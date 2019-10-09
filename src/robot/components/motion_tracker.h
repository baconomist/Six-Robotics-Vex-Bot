//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_MOTION_TRACKER_H
#define VEXROBOT_MOTION_TRACKER_H

#include "main.h"

class MotionTracker
{
public:
    ADIEncoder* leftEncoder;
    ADIEncoder* rightEncoder;
    ADIEncoder* centerEncoder;

    MotionTracker();

    void initialize();
    void update();

    float calculate_rotation_from_motion();

};

#endif //VEXROBOT_MOTION_TRACKER_H
