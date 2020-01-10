//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_DRIVE_H
#define VEXROBOT_DRIVE_H

#include <math.h>
#include "main.h"

/**
 * TTI: Ticks to inches
 * ITT: Inches to ticks
 * **/
extern const float TTI;
extern const float ITT;

int scale_motor_val(int speed, Motor *motor);

enum DriveMode
{
    DRIVE_MODE_TANK,
    DRIVE_MODE_ARCADE
};

class Drive
{
public:
    static DriveMode driveMode;

    static void move_left(float speed);

    static void move_right(float speed);

    static void move_straight(float speed);

    static void strafe(int speed);

    static void stop();

    static void turn(float speed);

    static void tank();

    static void arcade();

    static void arcade2();

    static void set_brake_all(motor_brake_mode_e brake_mode);

    static void update();

    static void initialize();
};


#endif //VEXROBOT_DRIVE_H
