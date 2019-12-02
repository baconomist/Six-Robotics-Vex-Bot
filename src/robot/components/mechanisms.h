#ifndef VEXROBOT_MECHANISMS_H
#define VEXROBOT_MECHANISMS_H

#include "../motion_control/PID.h"

enum TrayPosition
{
    TRAY_POSITION_UP,
    TRAY_POSITION_DOWN
};

enum LiftPosition
{
    LIFT_POSITION_UP,
    LIFT_POSITION_DOWN
};

class Mechanisms
{
public:
    static P *trayP;
    static P *liftP;

    static float get_tilter_pos();

    static float get_lift_pos();

    static void tilter(int speed);

    static void lifter(int speed);

    static void intake(int speed);

    static void set_tray_position(TrayPosition trayPosition);

    static void set_lift_position(LiftPosition liftPosition);

    static void update();

    static void initialize();
};

#endif
