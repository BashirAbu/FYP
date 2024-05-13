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
    void SetAcceleration(float acceleration);
    void SetDeceleration(float deceleration);
    void SetAccelerationTime(float accelerationTime);
    void SetDecelerationTime(float decelerationTime);
    
    struct ConfigData
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
    };
    struct StatusData
    {   
        float speed;
        float position;
        float acceleration;
        float deceleration;
    };
    ConfigData data;
private:
};