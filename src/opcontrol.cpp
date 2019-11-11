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

    initialize_mtp(50, 50);

    while (true)
    {
        //robot->update();
        update_mtp();
        pros::delay(20);
    }
}
