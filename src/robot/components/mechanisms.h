#ifndef VEXROBOT_MECHANISMS_H
#define VEXROBOT_MECHANISMS_H
#include "../motion_control/PID.h"
class Mechanisms
{
public:
    static void tilter(int speed);

    static void lifter(int speed);

    static void intake(int speed);

    static PD *trayPD;

    static float get_tray_pos();

    static void update();

    static void initialize();
};

#endif
