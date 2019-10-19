//
// Created by Lucas on 9/27/2019.
//

#include "../components/drive.h"
#include "../robot.h"
#include "../motors.h"
#include "motion_tracker.h"
#include "../ports.h"

// Movement of tracking wheels(in same distance units as distance to center of robot)
float deltaL;
float deltaR;

MotionTracker::MotionTracker()
{

}

void MotionTracker::initialize()
{
    // TODO: fix ports
    this->leftEncoder = new ADIEncoder(LEFT_X_ENCODER_TOP, LEFT_X_ENCODER_BOTTOM, false);
    this->rightEncoder = new ADIEncoder(RIGHT_X_ENCODER_TOP, RIGHT_X_ENCODER_BOTTOM, false);
    this->centerEncoder = new ADIEncoder(Y_ENCODER_TOP, Y_ENCODER_BOTTOM, false);
}

void MotionTracker::update()
{
    // TODO: add accumulators for delta_L, delta_R

    deltaL = Drive::ticks_to_inches(driveLF->get_position());
    deltaR = Drive::ticks_to_inches(driveRF->get_position());
    printf("%f\n", calculate_rotation_from_motion());
}

float MotionTracker::calculate_rotation_from_motion()
{
    // Distance from robot center to arc center
    float robot_center_radius_to_arc = 0;

    // Distance from center of robot to corresponding side
    float s_r = Robot::WHEEL_TO_CENTER_DIST;
    float s_l = Robot::WHEEL_TO_CENTER_DIST;

    // Distances/radii from center of arc to respective sides of robot
    float r_left = robot_center_radius_to_arc + s_l;
    float r_right = robot_center_radius_to_arc - s_r;

    // Radius to point of rotation
    float arc_length = 0;

    // radians = 2pi * d/360d
    // 2pi * d/360d * radius = radians * radius = arc length

    float delta_theta = (deltaL - deltaR) / (r_left + r_right);

    return delta_theta;
}
