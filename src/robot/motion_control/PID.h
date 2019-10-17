//
// Created by Lucas on 8/31/2019.
//

// Prevent's integral buildup before integral really comes into effect,
// without this the robot may overshoot its target
#ifndef PID_H
#define PID_H
const int MIN_ERROR_FOR_INTEGRAL = 500;
const int MIN_ERROR_RANGE = 10;

// Not constants as we may want to write a program to tune PID and change values
extern float Kp;
extern float Ki;
extern float Kd;

class P
{
public:
    P(float (*get_sensor_value)(), float end, void (*callback)(float speed));

    void update();

    bool finished();

private:
    // Error is the distance to target
    float error;
    float speed;

    float (*get_sensor_value)();

    float end;

    void (*callback)(float speed);
};

class PI
{
public:
    PI(float (*get_sensor_value)(), float end, void (*callback)(float speed));

    void update();

    bool finished();

private:
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
    PD(float (*get_sensor_value)(), float end, void (*callback)(float speed));

    void update();

    bool finished();

private:
    // Error is the distance to target
    float error;
    float speed;

    // Predicts the future value for the error/distance, then adjust speed accordingly
    float derivative;

    float previous_error = error;

    float dT = 0;
    float last_frame_time = pros::millis();

    float (*get_sensor_value)();

    float end;

    void (*callback)(float speed);
};

#endif