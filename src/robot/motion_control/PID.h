//
// Created by Lucas on 8/31/2019.
//

// Prevent's integral buildup before integral really comes into effect,
// without this the robot may overshoot its target
#ifndef PID
#define PID
const int MIN_ERROR_FOR_INTEGRAL = 500;
const int MIN_ERROR_RANGE = 10;
// Constants used for scaling, range(0, 1)
extern float Kp;
extern float Ki;
extern float Kd;
#endif
