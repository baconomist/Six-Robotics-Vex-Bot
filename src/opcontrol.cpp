//
// Created by Lucas on 9/27/2019.
//
#include "main.h"
#include "robot/robot.h"
#include <stdarg.h>
#include "robot/motors.h"
#include "robot/controllers.h"
#include "robot/motion_control/PID.h"
#include "robot/components/move_to_point.h"

void opcontrol()
{
    robot->robotMode = REMOTE_CONTROLLED;
    // robot->start_mainloop();

    //initialize_mtp(20, 20);

    // Auton::goto_pos(0, 20);
    // Auton::goto_pos(20, 20);
    // Auton::goto_pos(20, 0);
    // Auton::goto_pos(0, 0);

    while (true)
    {
        robot->update();
        //Auton::print_debug();
        //update_mtp();
        pros::delay(20);
    }
}
