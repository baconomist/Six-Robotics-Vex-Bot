//
// Created by Lucas on 9/27/2019.
//

#include "motion_tracker.h"
#include "../../ports.h"

MotionTracker::MotionTracker()
{

}

void MotionTracker::initialize()
{
    // TODO: fix ports
    this->leftEncoder = new ADIEncoder(LEFT_X_ENCODER_TOP, LEFT_X_ENCODER_BOTTOM, false);
    this->rightEncoder = new ADIEncoder(RIGHT_X_ENCODER_TOP, RIGHT_X_ENCODER_BOTTOM, false);
    this->centerEncoder = new ADIEncoder(Y_ENCODER_TOP, Y_ENCODER_BOTTOM, false);
}

void calculate_rotation()
{
    float left_difference;
}
