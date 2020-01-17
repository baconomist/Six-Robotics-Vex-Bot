//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_DRIVE_H
#define VEXROBOT_DRIVE_H

#include "main.h"


/**
 * TTI: Ticks to inches
 * ITT: Inches to ticks
 * **/
extern const float TTI;
extern const float ITT;

float map(float val, float curr_min, float curr_max, float tar_min, float tar_max, int power=1, _Bool use_sgn = true);

int scale_motor_val(int speed, Motor *motor,  int deadzone = 0, int p = 1);

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

    static int motor_speeds[128];
    static int deadZone;
};


#endif //VEXROBOT_DRIVE_H
