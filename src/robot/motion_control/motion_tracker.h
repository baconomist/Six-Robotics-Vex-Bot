//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_MOTION_TRACKER_H
#define VEXROBOT_MOTION_TRACKER_H

#include "main.h"

class MotionTracker
{
public:
    MotionTracker();

    ADIEncoder *leftEncoder;
    ADIEncoder *rightEncoder;
    ADIEncoder *centerEncoder;

    void initialize();

    void update();

    float calculate_rotation_from_motion();

private:
    float wheel_to_wheel_dist;
    float wheel_to_center_dist;
};

#endif //VEXROBOT_MOTION_TRACKER_H
