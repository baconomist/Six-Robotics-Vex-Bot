/**
 * All of our header files are included here.
 * Then globals is included in any necessary file.
 * And then, namespaces are used to reference the desired function/code.
 * **/

#ifndef VEXROBOT_GLOBALS_H
#define VEXROBOT_GLOBALS_H

#include "main.h"
#include "okapi/api.hpp"
#include "hardware.h"

extern pros::Controller master;
extern okapi::ChassisController* chassis;

#endif //VEXROBOT_GLOBALS_H
