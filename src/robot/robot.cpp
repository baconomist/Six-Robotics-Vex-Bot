//
// Created by Lucas on 9/27/2019.
//
#include "main.h"
#include "robot.h"

RobotMode Robot::robotMode = ROBOT_MODE_RC;

/**
* This must be called on the pros initialize() function in initialize.cpp
* **/
void Robot::initialize()
{
    Drive::initialize();
    Mechanisms::initialize();
    Auton::initialize();
}


void Robot::update()
{
    if (robotMode == ROBOT_MODE_RC)
    {
        Drive::update();
        Mechanisms::update();
    } else if (robotMode == ROBOT_MODE_AUTON)
        Auton::update();
    else
        lcd::print(1, "Something went horribly wrong");
    lcd::printf(1,"Tray: %f", Mechanisms::tilter_get_pos());
    lcd::printf(2,"Lift: %f", Mechanisms::lift_get_pos());
}
