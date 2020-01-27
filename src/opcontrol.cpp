#include "main.h"
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


using namespace hardware;
using namespace hardware::ports;
using namespace mechanisms;





void opcontrol() {
	auto meccanumDrive = std::dynamic_pointer_cast<XDriveModel>(chassisController->getModel());
    while (true) {
        int intakeDirection = master.getDigital(ControllerDigital::L1) - master.getDigital(ControllerDigital::L2);
        int tiltDirection = master.getDigital(ControllerDigital::R1) - master.getDigital(ControllerDigital::R2);
        int liftDirection = master.getDigital(ControllerDigital::X) - master.getDigital(ControllerDigital::B);
		bool override = master.getDigital(ControllerDigital::Y);



        if(!override) {
	        if (tiltDirection)
		        tray::move_tray_controlled(tiltDirection);
	        else if (liftDirection) {
		        lift::move_lift_raw((int)transT.getGearing() * liftDirection);
		        intakeMotors.moveVelocity((int)intakeMotors.getGearing()*intakeDirection);
	        }
	        else {
		        hold_transmission_motors();
		        intakeMotors.moveVelocity((int)intakeMotors.getGearing()*intakeDirection);
	        }
        }
        else{
	        intakeMotors.moveVelocity((int)intakeMotors.getGearing()*intakeDirection);
	        if (tiltDirection)
		        tray::move_tray_raw((int)transT.getGearing()*tiltDirection);
	        else if (liftDirection) {
		        lift::move_lift_raw((int)transT.getGearing() * tiltDirection);
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
        pros::lcd::print(1, "Tray: %lf", tray::get_tray_pos());
		pros::lcd::print(2, "Lift: %lf", liftPot.get());


		pros::delay(10);
    }
}
