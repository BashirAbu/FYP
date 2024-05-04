#pragma once
#include <stdint.h>


class ServoController
{
public:
    ServoController();
    ~ServoController();

    void SetSpeed(uint32_t speed);
    void SetPosition(int32_t position);
    

    struct ConfigData
    {   
        uint32_t speed;
        int32_t position;
        uint32_t encoderCounts;
    };
    ConfigData data;
private:
};