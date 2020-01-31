#include "main.h"
#include "globals.h"
#include "vision.h"

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


using namespace hardware;
using namespace hardware::ports;
using namespace mechanisms;

int intakeDirection;
int tiltDirection;
int liftDirection;
int liftState = 0;
bool override;
bool liftMoving = false;
ControllerButton buttonX = ControllerButton(ControllerDigital::X);
ControllerButton buttonB = ControllerButton(ControllerDigital::B);

void opcontrol() {
	auto meccanumDrive = std::dynamic_pointer_cast<XDriveModel>(chassisController->getModel());

//	autonomous();
	// test_vision();

	lift::control.setTarget(lift::state_to_pos(liftState));
	lift::control.reset();

	while (true) {
		intakeDirection = master.getDigital(ControllerDigital::L1) - master.getDigital(ControllerDigital::L2);
		tiltDirection = master.getDigital(ControllerDigital::R1) - master.getDigital(ControllerDigital::R2);
		liftDirection = buttonX.changedToPressed() - buttonB.changedToPressed();
		override = master.getDigital(ControllerDigital::Y);

		if (!override) {
			if (tiltDirection && (lift::control.isSettled() || tray::get_pos_raw() > lift::min_tray_pos_to_move_lift)) {
				tray::move_controlled(tiltDirection);
			}
			else if (liftDirection) {
				liftMoving = true;

				liftState += (liftState < 2 && liftDirection > 0) || (liftState > 0 && liftDirection < 0) ? liftDirection : 0;
				lift::control.setTarget(lift::state_to_pos(liftState));
				lift::control.reset();
			}
			else if (liftMoving) {
				if (tray::get_pos_raw() < lift::min_tray_pos_to_move_lift) {
					intakeMotors.moveVelocity((int)intakeMotors.getGearing() * intakeDirection);

					lift::control.flipDisable(false);
					if (!lift::control.isSettled()) {
						pros::lcd::print(2, "Lift: %lf", lift::get_pos_raw());
						double newOutput = lift::control.step(lift::get_pos_raw()) * (int)transT.getGearing();
						lift::move_raw(-newOutput);
					}
					else {
						liftMoving = false;
					}
				}
				else {
					tray::move_raw(30);
					lift::control.flipDisable(true);
				}
			}
			else {
				hold_transmission_motors();
				intakeMotors.moveVelocity((int)intakeMotors.getGearing() * intakeDirection);
			}
		}
		else {
			intakeMotors.moveVelocity((int)intakeMotors.getGearing() * intakeDirection);
			liftDirection = buttonX.isPressed() - buttonB.isPressed();
			if (tiltDirection)
				tray::move_raw((int)transT.getGearing() * tiltDirection);
			else if (liftDirection) {
				lift::move_raw((int)transT.getGearing() * liftDirection);
			}
			else {
				hold_transmission_motors();
			}
		}

		meccanumDrive->xArcade(
			master.getAnalog(ControllerAnalog::rightX),
			master.getAnalog(ControllerAnalog::leftY),
			master.getAnalog(ControllerAnalog::leftX)
		);

		pros::lcd::print(1, "LiftMoving: %d", liftMoving);
		pros::lcd::print(3, "Lift state: %d", liftState);
		pros::lcd::print(4, "Lift Speed?: %f", lift::control.getOutput() * (int)transT.getGearing());
		pros::lcd::print(5, "Settle Lift: %d Tray: %d", lift::control.isSettled(), tray::control.isSettled());
		pros::lcd::print(6, "Lift Target: %lf", lift::control.getTarget());
		pros::lcd::print(7, "Lift Error: %lf", lift::control.getError());

		pros::delay(10);
	}
}
