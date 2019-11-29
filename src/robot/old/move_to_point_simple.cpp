//
// Created by Lucas on 11/14/2019.
//

#include "move_to_point_simple.h"

#include "main.h"
#include "../motion_control/PID.h"
#include "../robot.h"
#include "../motors.h"
#include "../components/drive.h"

P *currentP;
float kP = 0.5f;

float x_diff, y_diff = 0;
float rot_target_radians = 0;
float move_distance = 0;
float turn_distance = 0;

void mtp_simple::update()
{

}

void mtp_simple::initialize(float target_x, float target_y)
{

}