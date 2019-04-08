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

 MotorGroup lD({2, 10});
 MotorGroup rD({-1, -9});

auto chassis = ChassisControllerFactory::create(
  lD, rD,
  AbstractMotor::gearset::red,
  {WHEEL_DIAMETER, CHASSIS_WIDTH}

);
auto profileController = AsyncControllerFactory::motionProfile(
  1.5,  // Maximum linear velocity of the Chassis in m/s
  1.0,  // Maximum linear acceleration of the Chassis in m/s/s
  5.0, // Maximum linear jerk of the Chassis in m/s/s/s
  chassis // Chassis Controller
);

void autonomous() {
    Rate rate;
    rate.delayUntil(1000);
    profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, 0_ft, 0_deg}}, "A");
    profileController.setTarget("A");



}
