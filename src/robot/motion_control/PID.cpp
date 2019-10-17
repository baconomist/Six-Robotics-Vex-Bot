//
// Created by Lucas on 8/31/2019.
//

// http://smithcsrobot.weebly.com/uploads/6/0/9/5/60954939/pid_control_document.pdf

#include "main.h"
#include "PID.h"
float Kp = 0.5;
float Kd = 0.01;
float Ki = 0.1;


void P(float (*get_sensor_value)(), float end, float (*yield_return)(float speed)){
    // Error is the distance to target
    float error;
    float speed;

    error = end - get_sensor_value();
    while (std::abs(error) > MIN_ERROR_RANGE)
    {
        error = end - get_sensor_value();
        speed = error * Kp;

        yield_return(speed);
    }
}

void PI(float (*get_sensor_value)(), float end, float (*yield_return)(float speed))
{
    float error = end - get_sensor_value();

    // Integral is used for small error calculation, keep the motors moving to fix small errors
    float integral = 0;

    float speed;

    float dT = 0;
    float last_frame_time = pros::millis();
    while (std::abs(error) > MIN_ERROR_RANGE)
    {
        dT = pros::millis() - last_frame_time;

        error = end - get_sensor_value();
        if (std::abs(error) < MIN_ERROR_FOR_INTEGRAL)
        integral = integral + error * dT;

        // When we've reached our destination, reset the integral to prevent from continuing to move
        if (error < 0)
        integral = 0;

        speed = error * Kp + integral * Ki;

        yield_return(speed);

        last_frame_time = pros::millis();
    }
}
//
// void PID( float(*get_sensor_value)(), float end, float (*yield_return)(float speed))
// {
//     float error = end - get_sensor_value();
//     float integral = 0;
//
//     float previous_error = error;
//
//     // Predicts the future value for the error/distance, then adjust speed accordingly
//     float derivative = 0;
//
//     float speed;
//
//     float dT = 0;
//     float last_frame_time = pros::millis();
//     while (std::abs(error) > MIN_ERROR_RANGE)
//     {
//         dT = pros::millis() - last_frame_time;
//
//         error = end - get_sensor_value();
//
//         // derivative == the next error
//         derivative = (error - previous_error) / dT;
//
//         if (std::abs(error) < MIN_ERROR_FOR_INTEGRAL)
//         integral = integral + error * dT;
//
//         // When we've reached our destination, reset the integral to prevent from continuing to move
//         if (error == 0)
//         integral = 0;
//
//         speed = error * Kp + integral * Ki + derivative * Kd;
//
//         yield_return(speed);
//
//         last_frame_time = pros::millis();
//         previous_error = error;
//     }
// }
