//
// Created by Lucas on 8/31/2019.
//

#include "motor_gearsets.h"
using namespace pros;
int get_gearset_rpm(motor_gearset_e gearset)
{
    switch (gearset)
    {
        case MOTOR_GEARSET_RED:
            return MOTOR_GEARSET_RED_RPM
        case MOTOR_GEARSET_GREEN:
            return MOTOR_GEARSET_GREEN_RPM
        case MOTOR_GEARSET_BLUE:
            return MOTOR_GEARSET_BLUE_RPM

        case E_MOTOR_GEARSET_INVALID:
            break;
    }
    return 0;
}
