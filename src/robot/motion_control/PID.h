//
// Created by Lucas on 8/31/2019.
//

// Prevent's integral buildup before integral really comes into effect,
// without this the robot may overshoot its target
#ifndef PID_H
#define PID_H

#include "main.h"

const int MIN_ERROR_FOR_INTEGRAL = 500;
const int MIN_ERROR_RANGE = 10;

class P
{
public:
    P(float Kp, float (*get_sensor_value)(), float end, void (*callback)(float speed),
      float error_range = MIN_ERROR_RANGE);

    void update();

    bool finished();

    float Kp;

    // Error is the distance to target
    float error;
    float speed;
    float error_range;

    float (*get_sensor_value)();

    float end;

    void (*callback)(float speed);
};

class PI
{
public:
    PI(float Kp, float Ki, float (*get_sensor_value)(), float end, void (*callback)(float speed));

    void update();

    bool finished();

private:
    float Kp;
    float Ki;

    // Error is the distance to target
    float error;
    float speed;
    float integral;

    float dT;
    float last_frame_time;

    float (*get_sensor_value)();

    float end;

    void (*callback)(float speed);
};

class PD
{
public:
    PD(float Kp, float Kd, float (*get_sensor_value)(), float end, void (*callback)(float speed));

    void update();

    bool finished();

    void reset(float newEnd);

private:
    float Kp;
    float Kd;

    bool maxPoint;

    // Error is the distance to target
    float error;
    float speed;

    // Predicts the future value for the error/distance, then adjust speed accordingly
    float derivative;

    float previous_error;

    float dT = 0;
    float last_frame_time = pros::millis();

    float (*get_sensor_value)();

    float end;

    void (*callback)(float speed);
};

class PID
{
public:
    PID(float Kp, float Ki, float Kd, float (*get_sensor_value)(), float end, void (*callback)(float speed));

    void update();

    bool finished();

private:
    float Kp;
    float Ki;
    float Kd;

    float error;
    float speed;

    float integral;
    float derivative;

    float previous_error;

    float dT = 0;
    float last_frame_time = pros::millis();

    float (*get_sensor_value)();

    float end;

    void (*callback)(float speed);
};

#endif
