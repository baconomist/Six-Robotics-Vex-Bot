#ifndef VEXROBOT_MECHANISMS_H
#define VEXROBOT_MECHANISMS_H
#include "../motion_control/PID.h"

class Mechanisms
{
public:
    //static PD *trayPD;
    //static PD *liftPD;
    static float tilter_get_pos();
    static float lift_get_pos();
    static void tilter_go_to_pos(const float *end);
    static void lifter_go_to_pos(const float *end);
    static bool calibrate_sensors();
    void tilter(int speed);

    void lifter(int speed);

    void intake(int speed);

    void update();

    void initialize();
};

#endif

