//
// Created by Lucas on 8/31/2019.
//

#include "main.h"
#include "ports.h"
#ifndef VEXROBOT_MOTORS_H // Only compile if this macro is not yet defined
#define VEXROBOT_MOTORS_H
#define driveLF pros::Motor(DRIVE_LF,E_MOTOR_GEARSET_18, false)
#define driveLB pros::Motor(DRIVE_LB, E_MOTOR_GEARSET_18, false)
#define driveRF pros::Motor(DRIVE_RF, E_MOTOR_GEARSET_18, true)//reserved
#define driveRB pros::Motor(DRIVE_RB, E_MOTOR_GEARSET_18, true)//reversed

#define transF pros::Motor(TRANS_F, E_MOTOR_GEARSET_36, false)
#define transB pros::Motor(TRANS_B, E_MOTOR_GEARSET_36, true)//reversed

#define intakeL pros::Motor(INTAKE_L, E_MOTOR_GEARSET_36, false)
#define intakeR pros::Motor(INTAKE_R, E_MOTOR_GEARSET_36, true)//reversed
#endif //VEXROBOT_MOTORS_H
