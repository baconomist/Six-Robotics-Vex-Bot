//
// Created by Lucas on 9/27/2019.
//

#include "robot.h"

Robot::Robot()
{
    this->drive = new Drive();
    this->motionTracker = new MotionTracker();
}

/**
 * This must be called on the pros initialize() function in initialize.cpp
 * **/
void Robot::initialize()
{
    this->motionTracker->initialize();
}

void Robot::start_mainloop()
{
    this->runningMainloop = true;
    while(this->runningMainloop)
    {
        this->drive->update();
    }
}

void Robot::end_mainloop()
{
    this->runningMainloop = false;
}

void Robot::update()
{}

void Robot::execute_next()
{}

void Robot::queue_action()
{}
