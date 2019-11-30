//
// Created by Lucas on 9/27/2019.
//
#include "main.h"
#include "robot/robot.h"
#include <stdarg.h>
#include "robot/motors.h"
#include "robot/ports.h"
#include "robot/controllers.h"
#include "robot/motion_control/PID.h"
#include "robot/old/move_to_point.h"



void opcontrol()
{
    Robot::robotMode = ROBOT_MODE_RC;
    Drive::driveMode = DRIVE_MODE_ARCADE;

    while (true)
    {
        Robot::update();
        //Auton::print_debug();
        //update_mtp();
        pros::delay(20);
    }
}
