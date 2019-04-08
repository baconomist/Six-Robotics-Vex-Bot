#include "main.h"
#include "okapi/api.hpp"

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
 using namespace okapi;

 auto myChassis = ChassisControllerFactory::create(
   {1, 9}, // Left motors
   {-2, -10},   // Right motors
   AbstractMotor::gearset::blue, // Torque gearset
   {4_in, 12.5_in} // 4 inch wheels, 12.5 inch wheelbase width
 );

 auto profileController = AsyncControllerFactory::motionProfile(
   0.25,  // Maximum linear velocity of the Chassis in m/s
   2.0,  // Maximum linear acceleration of the Chassis in m/s/s
   10.0, // Maximum linear jerk of the Chassis in m/s/s/s
   myChassis // Chassis Controller
 );

 void opcontrol() {
     okapi::Rate rate;
     rate.delayUntil(1000);
   profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{1_ft, 0_ft, 0_deg}}, "A");
   profileController.generatePath({Point{1_ft, 0_ft, 0_deg}, Point{1_ft, 0_ft, 90_deg}}, "B");
   profileController.setTarget("A");
   profileController.waitUntilSettled();
   profileController.setTarget("B");
   profileController.waitUntilSettled();
     pros::lcd::print(1, "GGGGGGGGGGGGGG");
 }
