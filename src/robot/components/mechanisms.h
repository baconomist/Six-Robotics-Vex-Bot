#ifndef VEXROBOT_MECHANISMS_H
#define VEXROBOT_MECHANISMS_H

#include "../motion_control/PID.h"

class Mechanisms
{
public:
//    static PD *trayPD;
//    static PD *liftPD;

    static float tilter_get_pos();

    static float lift_get_pos();

    static void tilter(int speed);

    static void lifter(int speed);

    static void intake(int speed);

    static void update();

    static void initialize();
};

#endif
