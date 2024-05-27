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
        uint8_t send = 0;
    };
    struct StatusData
    {   
        float speed = 0.0f;
        float position = 0.0f;
        float acceleration = 0.0f;
    };
    ConfigData data;
    StatusData status_data;
private:
};