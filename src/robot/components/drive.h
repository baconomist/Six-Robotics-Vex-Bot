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
    Drive(float wheel_to_wheel_dist, float wheel_to_center_dist);

    void move_left(int speed);
    void move_right(int speed);
    void move(int speed);

    void turn_on_point(int speed);
    void arc_turn(float radians, float outer_radius, int speed);

    void strafe(int speed);

    void tank();
    void arcade();

    void update();
    void initialize();

    void stop_motors();
private:
    float wheel_to_wheel_dist;
    float wheel_to_center_dist;
};


#endif //VEXROBOT_DRIVE_H
