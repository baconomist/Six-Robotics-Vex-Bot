//
// Created by Lucas on 8/31/2019.
//

#include "main.h"

#ifndef VEXROBOT_MOTORS_H // Only compile if this macro is not yet defined
#define VEXROBOT_MOTORS_H

// extern Motor* driveLB;
// extern Motor* driveLF;
// extern Motor* driveRB;
// extern Motor* driveRF;
// extern Motor* transB;
// extern Motor* transT;
#define driveLF pros::Motor(20,E_MOTOR_GEARSET_18, false)
#define driveLB pros::Motor(10, E_MOTOR_GEARSET_18, false)
#define driveRF pros::Motor(11, E_MOTOR_GEARSET_18, true)//reserved
#define driveRB pros::Motor(1, E_MOTOR_GEARSET_18, true)//reversed

#define transT pros::Motor(2, E_MOTOR_GEARSET_36, false)
#define transB pros::Motor(9, E_MOTOR_GEARSET_36, true)//reversed


#endif //VEXROBOT_MOTORS_H
