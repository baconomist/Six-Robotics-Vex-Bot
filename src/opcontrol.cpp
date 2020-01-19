#include "main.h"
#include "okapi/api.hpp"
#include "../src/globals.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

using namespace okapi::literals;
using namespace okapi;
using namespace hardware;
using namespace hardware::ports;

void opcontrol()
{
    Point point;
    point.x = 0_ft;
    point.y = 1_ft;
    printf("aaaa");
    //chassisController->moveDistance(12_in);
    //chassisController->waitUntilSettled();
    //chassisController->moveDistance(-12_in);
    chassisController->driveToPoint(point);
    chassisController->waitUntilSettled();
    printf("Settled");
    //chassisController->turnAngle(okapi::degree * 90);
    //chassisController->moveDistance(-okapi::inch * 12);
}

