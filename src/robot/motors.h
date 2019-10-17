//
// Created by Lucas on 8/31/2019.
//

#include "main.h"
#include "ports.h"

#ifndef VEXROBOT_MOTORS_H // Only compile if this macro is not yet defined
#define VEXROBOT_MOTORS_H

extern pros::Motor* driveLB;
extern pros::Motor* driveLF;
extern pros::Motor* driveRB;
extern pros::Motor* driveRF;
extern pros::Motor* transT;
extern pros::Motor* transB;
extern pros::Motor* intakeL;
extern pros::Motor* intakeR;

#endif //VEXROBOT_MOTORS_H
