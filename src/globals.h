//
// Created by Lucas on 1/17/2020.
//

#ifndef VEXROBOT_GLOBALS_H
#define VEXROBOT_GLOBALS_H

#include "main.h"
#include "okapi/api.hpp"
#include "hardware.h"

#define master pros::Controller(pros::E_CONTROLLER_MASTER)

extern okapi::ChassisController* chassis;

#endif //VEXROBOT_GLOBALS_H
