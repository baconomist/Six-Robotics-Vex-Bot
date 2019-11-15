//
// Created by Lucas on 11/14/2019.
//

#include "move_to_point_simple.h"

#include "main.h"
#include "../motion_control/PID.h"
#include "../robot.h"
#include "../motors.h"

void move_left(float speed)
{
    driveLF->move_velocity((int) speed);
    driveLB->move_velocity((int) speed);
}

void move_right(float speed)
{
    driveRF->move_velocity((int) speed);
    driveRB->move_velocity((int) speed);
}

float calculate_rotation_from_motion()
{
    // Distance from robot center to arc center
    float arc_length = 0;

    // Distance from center of robot to corresponding side
    float s_r = Robot::WHEEL_TO_CENTER_DIST;
    float s_l = Robot::WHEEL_TO_CENTER_DIST;

    // Distances/radii from center of arc to respective sides of robot
    float r_left = arc_length + s_l;
    float r_right = arc_length - s_r;

    // 2pi * d/360d * radius = radians * radius = arc length

    float delta_theta = (Drive::ticks_to_inches(get_l_pos()) - Drive::ticks_to_inches(get_r_pos())) / (s_l + s_r);

    return delta_theta;
}

P* currentP;
float kP = 0.5f;

float x_diff, y_diff = 0;
float rot_target_radians = 0;
float move_distance = 0;
float turn_distance = 0;

void update()
{

}

void initialize(float target_x, float target_y)
{
    x_diff = target_x - 0;
    y_diff = target_y - 0;
    rot_target_radians = (float) atan(x_diff / y_diff);
    move_distance = (float) sqrt(x_diff * x_diff + y_diff * y_diff);
    turn_distance = Robot::WHEEL_TO_CENTER_DIST * rot_target_radians;

    currentP = new P(kP, get_l_pos, Drive::inches_to_ticks(turn_distance))
}