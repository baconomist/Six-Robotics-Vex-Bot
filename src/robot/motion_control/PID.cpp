//
// Created by Lucas on 8/31/2019.
//

// http://smithcsrobot.weebly.com/uploads/6/0/9/5/60954939/pid_control_document.pdf

/**
 * @params: PID units are in encoder ticks
 * **/

#include "main.h"
#include "PID.h"

/**
 * P class
 * **/
P::P(float Kp, float (*get_sensor_value)(), float end, void (*callback)(float), float error_range) {
    this->Kp = Kp;

    this->get_sensor_value = get_sensor_value;
    this->end = end;
    this->callback = callback;
    this->error_range = error_range;

    // Error is the distance to target
    error = end - get_sensor_value();
}

void P::update() {
    error = end - get_sensor_value();
    speed = error*Kp;

    callback(speed);
}

bool P::finished() {
    return std::abs(error) < error_range;
}

/**
 * PI class
 * **/

PI::PI(float Kp, float Ki, float (*get_sensor_value)(), float end, void (*callback)(float)) {
    this->Kp = Kp;
    this->Ki = Ki;

    this->get_sensor_value = get_sensor_value;
    this->end = end;
    this->callback = callback;

    error = end - get_sensor_value();

    // Integral is used for small error calculation, keep the motors moving to fix small errors
    integral = 0;

    dT = 0;
    last_frame_time = pros::millis();
}

void PI::update() {
    dT = pros::millis() - last_frame_time;

    error = end - get_sensor_value();
    if (std::abs(error) < MIN_ERROR_FOR_INTEGRAL)
        integral = integral + error*dT;

    // When we've reached our destination, reset the integral to prevent from continuing to accumalate
    if (error < 0)
        integral = 0;

    speed = error*Kp + integral*Ki;

    callback(speed);

    last_frame_time = pros::millis();
}

bool PI::finished() {

    return std::abs(error) < MIN_ERROR_RANGE;
}

/**
 * PD class
 * **/

PD::PD(float Kp, float Kd, float (*get_sensor_value)(), float end, void (*callback)(float), bool maxPoint) {
    this->Kp = Kp;
    this->Kd = Kd;

    this->maxPoint = maxPoint;
    this->get_sensor_value = get_sensor_value;
    this->end = end;
    this->callback = callback;

    error = end - get_sensor_value();
    previous_error = error;

    // Integral is used for small error calculation, keep the motors moving to fix small errors
    derivative = 0;

    dT = 0;
    last_frame_time = pros::millis();
}

void PD::reset(float newEnd) {
    this->end = newEnd;
}

void PD::update() {
    dT = pros::millis() - last_frame_time;

    error = end - get_sensor_value();

    // derivative == the next error
    derivative = (error - previous_error)/dT;

    speed = error*Kp + derivative*Kd;

    callback(speed);

    last_frame_time = pros::millis();
    previous_error = error;
}

bool PD::finished() {
    if (this->maxPoint)
        return std::abs(error) < 0;

    return std::abs(error) < MIN_ERROR_RANGE;
}

/**
 * PID class
 * **/
PID::PID(float Kp, float Ki, float Kd, float (*get_sensor_value)(), float end, void (*callback)(float)) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;

    this->get_sensor_value = get_sensor_value;
    this->end = end;
    this->callback = callback;

    error = end - get_sensor_value();
    previous_error = error;

    integral = 0;
    derivative = 0;

    dT = 0;
    last_frame_time = pros::millis();
}

void PID::update() {
    dT = pros::millis() - last_frame_time;

    error = end - get_sensor_value();

    // derivative == the next error
    derivative = (error - previous_error)/dT;

    if (std::abs(error) < MIN_ERROR_FOR_INTEGRAL)
        integral = integral + error*dT;

    // When we've reached our destination, reset the integral to prevent from continuing to move
    if (error==0)
        integral = 0;

    speed = error*Kp + integral*Ki + derivative*Kd;

    callback(speed);

    last_frame_time = pros::millis();
    previous_error = error;
}

bool PID::finished() {
    return std::abs(error) < MIN_ERROR_RANGE;
}
