//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_DRIVE_H
#define VEXROBOT_DRIVE_H

enum DriveMode
{
    TANK,
    ARCADE
};


class Drive
{
public:
    DriveMode driveMode = ARCADE;

    //constructor
    Drive();
    ~Drive();

    static float ticks_to_inches(float ticks);
    static float inches_to_ticks(float inches);

    static void move_left(float speed);
    static void move_right(float speed);
    static void move_straight(float speed);
    static void strafe(int speed);
    static void turn(float speed);
    static void tank();
    static void arcade();

    void update();
    void initialize();

    void hold_motors();
};


#endif //VEXROBOT_DRIVE_H
