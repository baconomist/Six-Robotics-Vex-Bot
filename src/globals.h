/**
 * All of our header files are included here.
 * Then globals is included in any necessary file.
 * And then, namespaces are used to reference the desired function/code.
 * **/

#ifndef VEXROBOT_GLOBALS_H
#define VEXROBOT_GLOBALS_H

#include "hardware.h"
#include "mechanisms.h"
#include "autonomous.h"
#include "inertial.h"

extern Controller master;
extern std::shared_ptr<okapi::OdomChassisController> chassisController;
extern std::shared_ptr<okapi::OdomChassisController> _2_wheeled_chassisController;
extern std::shared_ptr<okapi::OdomChassisController> _4_wheeled_chassisController;

extern std::shared_ptr<XDriveModel> meccanumDrive;
extern ADIEncoder leftEncoder;
extern ADIEncoder rightEncoder;
extern ADIEncoder centerEncoder;

enum driveConfig {
    DRIVE_FOUR_WHEEL,
    DRIVE_TWO_WHEEL
};

void changeToDrive(driveConfig config);

//extern Motor driveLF;
//extern Motor driveLB;
//extern Motor driveRF;
//extern Motor driveRB;

#endif //VEXROBOT_GLOBALS_H
