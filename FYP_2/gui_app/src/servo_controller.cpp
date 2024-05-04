#include <servo_controller.h>


ServoController::ServoController()
{
    data = {0};
}

ServoController::~ServoController()
{
    
}

void ServoController::SetSpeed(uint32_t speed)
{
    data.speed = speed;
}

void ServoController::SetPosition(int32_t position)
{
    data.position = position;
}
