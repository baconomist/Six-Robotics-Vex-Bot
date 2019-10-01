//
// Created by Lucas on 9/27/2019.
//

#include "robot/robot.h"


void opcontrol()
{
    robot = new Robot();
    robot->robotMode = REMOTE_CONTROLLED;

    robot->start_mainloop();
}