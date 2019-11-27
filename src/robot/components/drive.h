//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_DRIVE_H
#define VEXROBOT_DRIVE_H

#include <math.h>

/**
 * TTI: Ticks to inches
 * ITT: Inches to ticks
 * **/
extern const float TTI;
extern const float ITT;

float operator""_ticks(long double inches);
int operator""_in(unsigned long long ticks);

enum DriveMode
{
    TANK,
    ARCADE
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

    static void update();
    static void initialize();
private:
    Drive();
    ~Drive();
};


#endif //VEXROBOT_DRIVE_H
