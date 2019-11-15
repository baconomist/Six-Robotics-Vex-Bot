//
// Created by Lucas on 9/27/2019.
//
#include "main.h"
#include "robot.h"

Robot::Robot()
{
    this->drive = new Drive();
    this->mechanisms = new Mechanisms();
}

/**
* This must be called on the pros initialize() function in initialize.cpp
* **/
void Robot::initialize()
{
    drive->initialize();
    mechanisms->initialize();
    Auton::initialize();
}


void Robot::start_mainloop()
{
    runningMainloop = true;
    while(runningMainloop)
    {

        //this->drive->update();
        mechanisms->update();
    }
}

void Robot::end_mainloop()
{
    this->runningMainloop = false;
}

void Robot::update()
{
    //drive->update();
    //mechanisms->update();
    Auton::update();
}

void Robot::execute_next()
{}

void Robot::queue_action()
{}
