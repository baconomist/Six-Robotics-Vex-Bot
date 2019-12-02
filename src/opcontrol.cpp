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
    // robot->start_mainloop();

    //Robot::robotMode = ROBOT_MODE_AUTON;

    //initialize_mtp(20, 20);

    //Auton::goto_pos(0, 20);
    //Auton::goto_pos(0, -20);
    //Auton::goto_pos(20, 0);
    // Auton::goto_pos(20, 20);
    // Auton::goto_pos(20, 0);
    // Auton::goto_pos(0, 0);

    while (true)
    {
        Robot::update();
        //update_mtp();
        pros::delay(20);
    }
}
