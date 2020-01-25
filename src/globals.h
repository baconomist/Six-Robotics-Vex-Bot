/**
 * All of our header files are included here.
 * Then globals is included in any necessary file.
 * And then, namespaces are used to reference the desired function/code.
 * **/

#ifndef VEXROBOT_GLOBALS_H
#define VEXROBOT_GLOBALS_H
#include "hardware.h"
#include "mechanisms.h"
extern Controller master;
extern std::shared_ptr<okapi::OdomChassisController> chassisController;

#endif //VEXROBOT_GLOBALS_H
