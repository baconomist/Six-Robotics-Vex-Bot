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

    static float ticks_to_inches(float ticks);
    static float inches_to_ticks(float inches);
    
    static void move_left(float speed);
    static void move_right(float speed);
    static void move(float speed);

    static void turn_on_point(float speed);
    void arc_turn(float radians, float outer_radius, int speed);

    void strafe(int speed);

    void tank();
    void arcade();

    void update();
    void initialize();

    void stop_motors();
};


#endif //VEXROBOT_DRIVE_H
