//
// Created by Lucas on 9/27/2019.
//
#include "main.h"
#include "robot/robot.h"
#include <stdarg.h>


void opcontrol()
{
  robot = new Robot();
  robot->robotMode = REMOTE_CONTROLLED;
}
