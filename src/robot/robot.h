//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_ROBOT_H
#define VEXROBOT_ROBOT_H

#include "components/drive.h"
#include "components/mechanisms.h"
#include "motion_control/motion_tracker.h"

enum RobotMode
{
    AUTONOMOUS,
    REMOTE_CONTROLLED
};

//TODO: create an auton class
class Robot
{
public:
    Drive* drive;
    Mechanisms* mechanisms;
    MotionTracker* motionTracker;
    RobotMode robotMode = AUTONOMOUS;
    bool runningMainloop = false;
    Robot(float wheel_diameter,float wheel_to_wheel_dist, float wheel_to_center_dist);

    void initialize();

    void start_mainloop();

    void end_mainloop();

    void update();

    void execute_next();

    void queue_action();
};

extern Robot* robot;

#endif //VEXROBOT_ROBOT_H
