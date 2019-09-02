//
// Created by Lucas on 8/31/2019.
//

#include <api.h>
#include "motor_gearsets.h"
#include "motor_ports.h"

Motor driveLF(LEFT_FRONT, MOTOR_GEARSET_GREEN);
Motor driveLB(LEFT_BACK, MOTOR_GEARSET_GREEN);
Motor driveRF(RIGHT_FRONT, MOTOR_GEARSET_GREEN);
Motor driveRB(RIGHT_BACK, MOTOR_GEARSET_GREEN);

Motor transB(TRANSMISSION_BOTTOM, MOTOR_GEARSET_RED);
Motor transT(TRANSMISSION_TOP, MOTOR_GEARSET_RED);
