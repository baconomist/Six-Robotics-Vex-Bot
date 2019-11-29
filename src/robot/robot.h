//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_ROBOT_H
#define VEXROBOT_ROBOT_H

#include "components/drive.h"
#include "components/mechanisms.h"
#include "motion_control/auton.h"

enum RobotMode
{
    ROBOT_MODE_AUTON,
    ROBOT_MODE_RC
};

//TODO: create an auton class
class Robot
{
public:
    // In inches
    constexpr static const float WHEEL_DIAMETER = 4.125f;
    constexpr static const float WHEEL_TO_WHEEL_DIST = 13.5f;
    constexpr static const float WHEEL_TO_CENTER_DIST = 7.75f;
    
    static RobotMode robotMode;

    static void update();

    static void initialize();
};

#endif //VEXROBOT_ROBOT_H
