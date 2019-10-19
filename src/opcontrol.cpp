//
// Created by Lucas on 9/27/2019.
//
#include "main.h"
#include "robot/robot.h"
#include <stdarg.h>
#include "robot/motors.h"
#include "robot/controllers.h"
#include "robot/motion_control/PID.h"

void opcontrol()
{
    robot->robotMode = REMOTE_CONTROLLED;
    // robot->start_mainloop();

    while (true)
    {
        robot->update();
        
        pros::delay(20);
    }
}
