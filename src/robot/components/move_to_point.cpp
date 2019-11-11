//
// Created by Lucas on 11/8/2019.
//

#include <cmath>
#include "../robot.h"
#include "../motors.h"
#include "move_to_point.h"
#include "../motion_control/PID.h"
#include "drive.h"
#include "motor_gearsets.h"

float clamp(float a, float min, float max)
{
    if (a < min)
        return min;
    if (a > max)
        return max;
    return a;
}

float clamp01(float a)
{
    return clamp(a, 0, 1);
}

float lerp(float a, float min, float max)
{
    return clamp01((a - min) / max);
}

float get_l_pos()
{ return driveLF->get_position(); }


float get_r_pos()
{ return driveRF->get_position(); }

float get_rotation_r_pos()
{
    // return get_r_pos() -
    return 0;
}

float get_pos()
{ return (get_l_pos() + get_r_pos()) / 2; }

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

float rotation_radians = 0;
float move_distance = 0;
float turn_distance = 0;

float rot_speed_left = 0;
float rot_speed_right = 0;

float max_motor_speed = MOTOR_GEARSET_GREEN_RPM;

P *moveP;
P *turnP;

void update_mtp()
{
    if (!moveP->finished())
        moveP->update();
    else
    {
        move_left(0);
        move_right(0);
    }
}

float x_diff = 0;
float y_diff = 0;
void initialize_mtp(float target_x, float target_y)
{
    // 0 being the robot position for now
    x_diff = target_x - 0;
    y_diff = target_y - 0;
    rotation_radians = (float) atan(x_diff / y_diff);
    move_distance = (float) sqrt(x_diff * x_diff + y_diff * y_diff);
    turn_distance = Robot::WHEEL_TO_CENTER_DIST * rotation_radians;

    float kP = 0.5f;
    moveP = new P(kP, get_l_pos, Drive::inches_to_ticks(move_distance + turn_distance), [](float speed) {
        speed = clamp(speed, 0, max_motor_speed) * (fabs(calculate_rotation_from_motion()) / rotation_radians);
        move_left(speed + rot_speed_left);
        move_right(speed + rot_speed_right);

        if ((float) fabs(calculate_rotation_from_motion()) >= rotation_radians)
            rot_speed_left = 0;
        else
            rot_speed_left = 50;
        rot_speed_right = -rot_speed_left;

        pros::lcd::print(5, "rot_speed: %f, speed_right: %f", rot_speed_left, speed + rot_speed_right);
        pros::lcd::print(6, "speed_left: %f", speed + rot_speed_left);

        printf("rot_speed: %f, speed: %f\n", rot_speed_left, speed + rot_speed_right);
    });
}


