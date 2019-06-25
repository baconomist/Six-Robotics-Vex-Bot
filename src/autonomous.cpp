#include "main.h"
#include "okapi/api.hpp"

using namespace okapi;

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

//1,9 L
//2,10 R
const auto WHEEL_DIAMETER = 4_in;
const auto CHASSIS_WIDTH = 13.5_in;

void autonomous()
{
    
}
