//
// Created by Lucas on 9/27/2019.
//
#include "main.h"
#include "robot.h"

Robot::Robot()
{
    this->drive = new Drive();
    this->mechanisms = new Mechanisms();
    //this->auton = new Auton();
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



void Robot::update()
{
    if(this->robotMode==REMOTE_CONTROLLED){
        drive->update();
        mechanisms->update();
    }
    else if(this->robotMode==AUTONOMOUS)
        Auton::update();
    else
        lcd::print(1, "Something went horribly wrong");
}

void Robot::execute_next()
{}

void Robot::queue_action()
{}
