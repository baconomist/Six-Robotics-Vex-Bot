//
// Created by Lucas on 8/31/2019.
//

#include "main.h"
#include "ports.h"

#ifndef VEXROBOT_MOTORS_H // Only compile if this macro is not yet defined
#define VEXROBOT_MOTORS_H

// extern Motor* driveLB;
// extern Motor* driveLF;
// extern Motor* driveRB;
// extern Motor* driveRF;
// extern Motor* transB;
// extern Motor* transT;
#define driveLF pros::Motor(LEFT_FRONT,E_MOTOR_GEARSET_18, false)
#define driveLB pros::Motor(LEFT_BACK, E_MOTOR_GEARSET_18, false)
#define driveRF pros::Motor(RIGHT_FRONT, E_MOTOR_GEARSET_18, true)//reserved
#define driveRB pros::Motor(RIGHT_BACK, E_MOTOR_GEARSET_18, true)//reversed

#define transT pros::Motor(TRANSMISSION_TOP, E_MOTOR_GEARSET_36, false)
#define transB pros::Motor(TRANSMISSION_BOTTOM, E_MOTOR_GEARSET_36, true)//reversed


#endif //VEXROBOT_MOTORS_H
