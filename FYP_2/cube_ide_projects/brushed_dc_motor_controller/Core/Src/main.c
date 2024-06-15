/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#define RECIEVED_BUFFER_SIZE 4
#define PWM_CLOCKWISE_CHANNEL TIM_CHANNEL_1
#define GPIO_CLOCKWISE_PIN GPIO_PIN_12 // port B
#define GPIO_COUNTER_CLOCKWISE_PIN GPIO_PIN_13 // Port B
#define PWM_COUNTER_CLOCKWISE_CHANNEL TIM_CHANNEL_2
#define PWM_DEADTIME_DELAY 1
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */


typedef enum MotorDirection
{
	ClockWise = 0,
	CounterClockWise,
  none
}MotorDirection;
typedef struct ConfigData
{
	float speed;
	float position;
	float acceleration;
	float deceleration;
	float accelerationTime;
	float decelerationTime;
	float encoderPulses;
	float gearRatio;
	float ki;
	float kp;
	float kd;
	uint8_t send;
} ConfigData;

typedef struct StatusData
{
	float motor_current_speed;
	float motor_current_position;
	float motor_current_acceleration;
	float dummy;
} StatusData;


MotorDirection motorDirection = ClockWise;
MotorDirection prevMotorDirection = none;

float filt_speed_1 = 0.001f;
float motor_speed_1 = 0.001f;

uint32_t PWM_CurrentChannel = PWM_CLOCKWISE_CHANNEL;
uint32_t PWM_countingDutyCycle = 0;


uint8_t rx_buffer[1];
uint8_t buffer[256];
uint8_t bufferIndex = 0;
ConfigData data;

float motor_current_position;
float motor_prev_position;
float motor_current_speed = 1.0f;
float motor_current_acceleration;
float _time;

// position PID
uint32_t currentTime;
float deltaTime;
uint32_t prevTime;


float errorValue;
float prevErrorValue;
float derivative;
float integral;
float controlSignal = 0.0f;
static float fs = 0.0f;
//Motion Profile
typedef struct MotionProfile
{
	float max_acceleration;
	float max_deceleration;
	float total_distance;
	float distance_to_max_velocity;
	float distance_to_stop;
	float distance_at_max_velocity;
	float time_to_max_velocity;
	float time_at_max_velocity;
	float time_to_stop;
	float total_time;
	float max_velocity;
  float initial_velocity;
  float initial_position;
  MotorDirection dir;
} MotionProfile;

MotionProfile motionProfile;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
float PulsestoDegrees(float pulses)
{
	return ((pulses * 360.0f) / (data.gearRatio * data.encoderPulses));
}


void CalculateMotionProfile()
{
	memset(&motionProfile, 0, sizeof(motionProfile));

  if(data.position < PulsestoDegrees(motor_current_position))
    motionProfile.dir = ClockWise;
  else
    motionProfile.dir = CounterClockWise;

	motionProfile.max_acceleration = data.acceleration;
	motionProfile.max_deceleration = data.deceleration;
  motionProfile.initial_velocity = fs;
  motionProfile.initial_position = PulsestoDegrees(motor_current_position);
	motionProfile.total_distance = fabs((data.position) - (PulsestoDegrees(motor_current_position)));
	motionProfile.max_velocity = motionProfile.dir == ClockWise? -data.speed : data.speed;
	if(motionProfile.max_acceleration == 0.0f || motionProfile.max_deceleration == 0.0f || motionProfile.max_velocity == 0.0f)
		return;
	motionProfile.time_to_max_velocity = fabs((motionProfile.max_velocity - motionProfile.initial_velocity) / motionProfile.max_acceleration);
	motionProfile.time_to_stop = fabs((motionProfile.max_velocity) / -motionProfile.max_deceleration);

	motionProfile.distance_to_max_velocity = 0.5 * motionProfile.max_acceleration * (float)pow(motionProfile.time_to_max_velocity, 2);
	motionProfile.distance_to_stop = 0.5 * motionProfile.max_deceleration * (float)pow(motionProfile.time_to_stop, 2);
	motionProfile.distance_at_max_velocity = motionProfile.total_distance - (motionProfile.distance_to_max_velocity + motionProfile.distance_to_stop);
  
	motionProfile.time_at_max_velocity = fabs(motionProfile.distance_at_max_velocity / motionProfile.max_velocity);
  motionProfile.total_time = motionProfile.time_at_max_velocity + motionProfile.time_to_max_velocity + motionProfile.time_to_stop;

  motionProfile.max_deceleration *= -1;
  if(motionProfile.dir == ClockWise)
  {
    motionProfile.distance_at_max_velocity *= -1;
    motionProfile.distance_to_max_velocity *= -1;
    motionProfile.distance_to_stop *= -1;
    motionProfile.total_distance *= -1;
    motionProfile.max_acceleration *= -1;
    motionProfile.max_deceleration *= -1;
  }
}

float GetPostionAtTime()
{
  float currentPos = 0.0f;
  
  if (_time <= motionProfile.time_to_max_velocity)
  {
    currentPos = motionProfile.initial_position + (motionProfile.initial_velocity * _time + 0.5f * ( motionProfile.max_acceleration * pow(_time, 2)));
  }
  else if(_time <= motionProfile.time_to_max_velocity + motionProfile.time_at_max_velocity)
  {
    currentPos = motionProfile.initial_position + motionProfile.distance_to_max_velocity + (motionProfile.max_velocity * (_time - motionProfile.time_to_max_velocity));
  }
  else if(_time <= motionProfile.total_time)
  {
    float v = ((motionProfile.max_velocity * (_time - (motionProfile.time_to_max_velocity + motionProfile.time_at_max_velocity))) + 0.5f * motionProfile.max_deceleration * pow((_time - (motionProfile.time_to_max_velocity + motionProfile.time_at_max_velocity)), 2));
    currentPos =  motionProfile.initial_position + motionProfile.distance_to_max_velocity + motionProfile.distance_at_max_velocity + v;
  }
  else
  {
    currentPos = motionProfile.initial_position + motionProfile.distance_to_max_velocity + motionProfile.distance_at_max_velocity + motionProfile.distance_to_stop;
  }
  return currentPos;
}

float get_current_position(MotionProfile* profile, float elapsed_time) {
    float current_position = profile->initial_position;
    float current_velocity = profile->initial_velocity;

    // Acceleration phase
    if (elapsed_time <= profile->time_to_max_velocity) {
    	if(profile->dir == ClockWise)
    	{
    		current_position -= profile->initial_velocity * elapsed_time + 0.5 * profile->max_acceleration * pow(elapsed_time, 2);
    	}
    	else
    	{
    		current_position += profile->initial_velocity * elapsed_time + 0.5 * profile->max_acceleration * pow(elapsed_time, 2);
    	}
    }
    // Constant velocity phase
    else if (elapsed_time <= (profile->time_to_max_velocity + profile->time_at_max_velocity)) {
      if(profile->dir == ClockWise)
    	{
        float acceleration_time = profile->time_to_max_velocity;
        float constant_velocity_time = elapsed_time - acceleration_time;
        current_position = profile->initial_position + (-profile->distance_to_max_velocity + profile->max_velocity * constant_velocity_time);
      }
      else
      {
        float acceleration_time = profile->time_to_max_velocity;
        float constant_velocity_time = elapsed_time - acceleration_time;
        current_position = profile->initial_position + (profile->distance_to_max_velocity + profile->max_velocity * constant_velocity_time);
      }
    }
    // Deceleration phase
    else if (elapsed_time <= profile->total_time) 
    {
    	if(profile->dir == ClockWise)
      {
        float acceleration_time = profile->time_to_max_velocity;
        float constant_velocity_time = profile->time_at_max_velocity;
        float deceleration_time = elapsed_time - (acceleration_time + constant_velocity_time);
        current_position = -(current_position + profile->distance_to_max_velocity + profile->distance_at_max_velocity) + profile->max_velocity * deceleration_time - 0.5 * -profile->max_deceleration * pow(deceleration_time, 2);
      }
      else
      {
        float acceleration_time = profile->time_to_max_velocity;
        float constant_velocity_time = profile->time_at_max_velocity;
        float deceleration_time = elapsed_time - (acceleration_time + constant_velocity_time);
        current_position += profile->distance_to_max_velocity + profile->distance_at_max_velocity + profile->max_velocity * deceleration_time - 0.5 * profile->max_deceleration * pow(deceleration_time, 2);
      }
    }
    // If elapsed_time exceeds total_time, return final position
    else {
      if(profile->dir == ClockWise)
      {
        current_position = (profile->initial_position - profile->total_distance);
      }
      else
      {
        current_position = (profile->initial_position + profile->total_distance);
      }
    }

    return current_position;
}


float GetVelocityAtTime()
{
	float velocity;
	//Acceleration Phase
	if(_time < motionProfile.time_to_max_velocity)
	{
    if(motionProfile.initial_velocity > motionProfile.max_velocity)
		  velocity = motionProfile.initial_velocity + motionProfile.max_acceleration * _time;
    else
      velocity = motionProfile.initial_velocity + motionProfile.max_acceleration * _time;
	}
	//Max Velocity Phase
	else if(_time < (motionProfile.time_at_max_velocity + motionProfile.time_to_max_velocity))
	{
		velocity = motionProfile.max_velocity;
	}
	//Deceleration Phase
	else if (_time < (motionProfile.total_time))
	{
    if(motionProfile.initial_velocity > motionProfile.max_velocity)
		  velocity = motionProfile.max_velocity + (motionProfile.max_deceleration * (_time - motionProfile.time_at_max_velocity - motionProfile.time_to_max_velocity));
    else
      velocity = motionProfile.max_velocity + (motionProfile.max_deceleration * (_time - motionProfile.time_at_max_velocity - motionProfile.time_to_max_velocity));
		
	}
	else
	{
		velocity = 0.0f;
	}
  return velocity;
}



void CalculateSpeed()
{
	motor_current_speed = (PulsestoDegrees(motor_current_position) - PulsestoDegrees(motor_prev_position)) / deltaTime;
	motor_prev_position = motor_current_position;
}

void CalculatePID()
{

	currentTime = HAL_GetTick();
	deltaTime = (float)((float)(currentTime) - (float)(prevTime)) / 1000.0f;

	_time = _time + deltaTime;

  if (!isnanf(motor_current_speed) && !isinf(motor_current_speed))
  {
    fs = 0.1f * motor_current_speed + (1.0f - 0.1f) * fs;
  }


	errorValue = GetPostionAtTime() - PulsestoDegrees(motor_current_position);
	//errorValue = GetVelocityAtTime() - fs;
	derivative = (errorValue - prevErrorValue) / deltaTime;
	integral = integral + errorValue * deltaTime;

	controlSignal = data.kp * errorValue + data.ki * integral + data.kd * derivative;

	char msg[255];
  sprintf(msg, "%d %d %d %d\n\0", (int)GetVelocityAtTime(), (int)fs, (int)PulsestoDegrees(motor_current_position), (int)GetPostionAtTime());
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	prevTime = currentTime;
	prevErrorValue = errorValue;
}

void DriveMotor()
{

	if(controlSignal < 0)
	{
		motorDirection = ClockWise;
	}
	else
	{
		motorDirection = CounterClockWise;
	}

	if(prevMotorDirection != motorDirection)
	{
		switch(motorDirection)
		{
		case ClockWise:
		{
		  PWM_CurrentChannel = PWM_CLOCKWISE_CHANNEL;
		  __HAL_TIM_SET_COMPARE(&htim2, PWM_COUNTER_CLOCKWISE_CHANNEL, 0);
		  __HAL_TIM_SET_COMPARE(&htim2, PWM_CLOCKWISE_CHANNEL, 0);
		  //delay here
		  //HAL_Delay(PWM_DEADTIME_DELAY);
		  __HAL_TIM_SET_COMPARE(&htim2, PWM_CurrentChannel, 0);
		  HAL_GPIO_WritePin(GPIOB, GPIO_COUNTER_CLOCKWISE_PIN, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_CLOCKWISE_PIN, GPIO_PIN_RESET);

		}break;
		case CounterClockWise:
		{
		  PWM_CurrentChannel = PWM_COUNTER_CLOCKWISE_CHANNEL;
		  __HAL_TIM_SET_COMPARE(&htim2, PWM_CLOCKWISE_CHANNEL, 0);
		  __HAL_TIM_SET_COMPARE(&htim2, PWM_COUNTER_CLOCKWISE_CHANNEL, 0);
		  //delay here
		 // HAL_Delay(PWM_DEADTIME_DELAY);
		  __HAL_TIM_SET_COMPARE(&htim2, PWM_CurrentChannel, 0);
		  HAL_GPIO_WritePin(GPIOB, GPIO_CLOCKWISE_PIN, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_COUNTER_CLOCKWISE_PIN, GPIO_PIN_RESET);
		}break;
		}
	}

	//setting PWM value
	PWM_countingDutyCycle = (uint32_t)fabs(controlSignal);
	if(PWM_countingDutyCycle > 180)
	{
		PWM_countingDutyCycle = 180;
	}
    __HAL_TIM_SET_COMPARE(&htim2, PWM_CurrentChannel, PWM_countingDutyCycle);

	prevMotorDirection = motorDirection;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(&huart1, rx_buffer, 1);
	if(rx_buffer[0] == '\n')
	{
    int p, s, a, d;
    sscanf(buffer, "%d %d %d %d", &p, &s, &a, &d);
    memset(buffer, 0, 256);
    data.position = p;
    data.speed = s;
    data.acceleration = a;
    data.deceleration = d;
		bufferIndex = 0;
		_time = 0.0f;
		integral = 0.0f;
    controlSignal = 0.0f;
		CalculateMotionProfile();
    return;
	}
	buffer[bufferIndex] = rx_buffer[0];
	bufferIndex++;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == GPIO_PIN_6)
  {
	  int32_t inc = 0;
	  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))
	  {
		   inc = 1;
	  }
	  else
	  {
		  inc = -1;
	  }
	  motor_current_position += (float)inc;
  }
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if(htim == &htim3)
	{
		StatusData send_data = {0};
		send_data.motor_current_position = motor_current_position;
		send_data.motor_current_speed = motor_current_speed;
		send_data.motor_current_acceleration= motor_current_acceleration;
		send_data.dummy = 1212.22f;
		//if(data.send)
			//HAL_UART_Transmit_IT(&huart1, (uint8_t*)&send_data, sizeof(StatusData));
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, rx_buffer, 1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_Base_Start_IT(&htim3);
  data.gearRatio = 3249.0f / 121.0f;
  data.encoderPulses = 500.0f;

  data.kp = 2.00f;
  data.ki = 0.1f;
  data.kd = 0.1f;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  CalculateSpeed();
	  CalculatePID();
	  DriveMotor();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 255;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 125;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 0;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 128 - 1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535 - 1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB12 PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
