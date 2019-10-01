//
// Created by Lucas on 9/27/2019.
//

#include "motion_tracker.h"

MotionTracker::MotionTracker()
{

}

void MotionTracker::initialize()
{
    // TODO: fix ports
    this->leftEncoder = new ADIEncoder(0, 0, false);
    this->rightEncoder = new ADIEncoder(0, 0, false);
    this->centerEncoder = new ADIEncoder(0, 0, false);
}

void calculate_rotation()
{
    float left_difference
}