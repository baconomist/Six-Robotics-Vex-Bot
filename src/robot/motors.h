//
// Created by Lucas on 8/31/2019.
//

#include "main.h"
#include "../ports.h"

#ifndef VEXROBOT_MOTORS_H // Only compile if this macro is not yet defined
#define VEXROBOT_MOTORS_H

#define driveLF pros::Motor(LEFT_FRONT,E_MOTOR_GEARSET_18, false)
#define driveLB pros::Motor(LEFT_BACK, E_MOTOR_GEARSET_18, false)
#define driveRF pros::Motor(RIGHT_FRONT, E_MOTOR_GEARSET_18, true)//reserved
#define driveRB pros::Motor(RIGHT_BACK, E_MOTOR_GEARSET_18, true)//reversed

#define transT pros::Motor(TRANSMISSION_TOP, E_MOTOR_GEARSET_36, false)
#define transB pros::Motor(TRANSMISSION_BOTTOM, E_MOTOR_GEARSET_36, true)//reversed

#define intakeL pros::Motor(INTAKE_LEFT, E_MOTOR_GEARSET_18, false)
#define intakeR pros::Motor(INTAKE_RIGHT, E_MOTOR_GEARSET_18, true)


#endif //VEXROBOT_MOTORS_H
