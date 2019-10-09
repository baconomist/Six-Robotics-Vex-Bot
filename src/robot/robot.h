//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_ROBOT_H
#define VEXROBOT_ROBOT_H

#include "components/drive.h"
#include "components/motion_tracker.h"

enum RobotMode
{
    AUTONOMOUS,
    REMOTE_CONTROLLED
};

class Robot
{
public:
    Drive* drive;
    MotionTracker* motionTracker;
    RobotMode robotMode = AUTONOMOUS;
    bool runningMainloop = false;

    Robot();

    void initialize();

    void start_mainloop();

    void end_mainloop();

    void update();

    void execute_next();

    void queue_action();
};

extern Robot* robot;

#endif //VEXROBOT_ROBOT_H
