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
    // In inches
    constexpr static const float WHEEL_DIAMETER = 4.125f;
    constexpr static const float WHEEL_TO_WHEEL_DIST = 13.5f;
    constexpr static const float WHEEL_TO_CENTER_DIST = 7.75f;

    Drive* drive;
    Mechanisms* mechanisms;
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
