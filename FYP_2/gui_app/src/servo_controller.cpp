#include <servo_controller.h>


ServoController::ServoController()
{
    data = {0};
}

ServoController::~ServoController()
{
    
}

void ServoController::SetSpeed(float speed)
{
    data.speed = speed;
}

void ServoController::SetPosition(float position)
{
    data.position = position;
}
void ServoController::SetGearRatio(float ratio)
{
    data.gearRatio = ratio;
}
void ServoController::SetEncoderPulses(float encoderPulses)
{
    data.encoderPulses = encoderPulses;
}
void ServoController::SetKi(float ki)
{
    data.ki = ki;
}
void ServoController::SetKp(float kp)
{
    data.kp = kp;
}
void ServoController::SetKd(float kd)
{
    data.kd = kd;
}

void ServoController::SetAcceleration(float acceleration)
{
    data.acceleration = acceleration;
}

void ServoController::SetDeceleration(float deceleration)
{
    data.deceleration = deceleration;
}

void ServoController::SetAccelerationTime(float accelerationTime)
{
    data.accelerationTime = accelerationTime;
}

void ServoController::SetDecelerationTime(float decelerationTime)
{
    data.decelerationTime = decelerationTime;
}
