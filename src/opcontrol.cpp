#include "main.h"
#include "okapi/api.hpp"
#include "globals.h"

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
	auto mecanumDrive = std::dynamic_pointer_cast<XDriveModel>(chassisController->getModel());
	while (true)
	{
		int intakeDirection = master.getDigital(ControllerDigital::L1) - master.getDigital(ControllerDigital::L2);
		int tiltDirection = master.getDigital(ControllerDigital::R1) - master.getDigital(ControllerDigital::R2);
		int liftDirection = master.getDigital(ControllerDigital::X) - master.getDigital(ControllerDigital::B);

		intakeMotors.moveVoltage(12000 * intakeDirection);

		if (tiltDirection)
		{
			transB.moveVoltage(12000 * tiltDirection);
			transT.moveVoltage(12000 * tiltDirection);
		}
		else if (liftDirection)
		{
			transB.moveVoltage(12000 * -liftDirection);
			transT.moveVoltage(12000 * liftDirection);
		}
		else
		{
			transB.moveVoltage(0);
			transT.moveVoltage(0);
		}

		mecanumDrive->xArcade(master.getAnalog(ControllerAnalog::rightX),
			master.getAnalog(ControllerAnalog::leftY),
			master.getAnalog(ControllerAnalog::leftX));
		pros::delay(10);
	}
}

