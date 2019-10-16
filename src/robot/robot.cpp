//
// Created by Lucas on 9/27/2019.
//

#include "robot.h"
Robot::Robot(float wheel_to_wheel_dist, float wheel_to_center_dist)
{
  this->drive = new Drive(wheel_to_wheel_dist, wheel_to_center_dist);
  this->mechanisms = new Mechanisms();
  this->motionTracker = new MotionTracker();
}

/**
* This must be called on the pros initialize() function in initialize.cpp
* **/
void Robot::initialize()
{
  this->motionTracker->initialize();
  this->drive->initialize();
  this->mechanisms->initialize();
}


void Robot::start_mainloop()
{
  this->runningMainloop = true;
  while(this->runningMainloop)
  {
    this->drive->update();
    this->mechanisms->update();
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
