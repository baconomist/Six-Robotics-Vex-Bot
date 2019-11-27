#ifndef VEXROBOT_MECHANISMS_H
#define VEXROBOT_MECHANISMS_H

class Mechanisms
{
public:
    static void tilter(int speed);

    static void lifter(int speed);

    static void intake(int speed);

    static float get_tray_pos();

    static void update();

    static void initialize();
};

#endif
