#pragma once
#include <stdint.h>


class ServoController
{
public:
    ServoController();
    ~ServoController();

    void SetSpeed(float speed);
    void SetPosition(float position);
    void SetGearRatio(float ratio);
    void SetEncoderPulses(float encoderPulses);
    void SetKi(float ki);
    void SetKp(float kp);
    void SetKd(float kd);
    

    struct ConfigData
    {   
        float speed;
        float position;
        float encoderPulses;
        float gearRatio;
        float ki;
        float kp;
        float kd;
    };
    ConfigData data;
private:
};