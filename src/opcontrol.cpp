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

ADIPotentiometer tray(TRAY_POT);
ADIPotentiometer lift(LIFT_POT);

void opcontrol()
{
    Robot::robotMode = ROBOT_MODE_RC;
    Drive::driveMode = DRIVE_MODE_ARCADE;
    // robot->start_mainloop();
    tray.calibrate();
    lift.calibrate();
    pros::delay(500);

    Robot::robotMode = ROBOT_MODE_AUTON;

    //initialize_mtp(20, 20);

    //Auton::goto_pos(0, 20);
    Auton::goto_pos(0, -20);
    // Auton::goto_pos(20, 20);
    // Auton::goto_pos(20, 0);
    // Auton::goto_pos(0, 0);

    while (true)
    {
        Robot::update();
        Auton::print_debug();
        //update_mtp();
        pros::delay(20);
    }
}
