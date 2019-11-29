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
    static PD *liftPD;
    static float tilter_get_pos();
    static float lift_get_pos();
    static void tilter_go_to_pos(const float *end);
    static void lifter_go_to_pos(const float *end);
    static bool calibrate_sensors();

    static void update();

    static void initialize();
private:
    static Task task;

};

#endif
