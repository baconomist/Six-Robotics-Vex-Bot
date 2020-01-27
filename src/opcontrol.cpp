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
//    autonomous();

	auto meccanumDrive = std::dynamic_pointer_cast<XDriveModel>(chassisController->getModel());
	int intakeDirection;
	int tiltDirection;
	int liftDirection;
	int liftState = 0;
	bool override;
	ControllerButton buttonX = ControllerButton(ControllerDigital::X);
	ControllerButton buttonB = ControllerButton(ControllerDigital::B);
	while (true) {

		intakeDirection = master.getDigital(ControllerDigital::L1) - master.getDigital(ControllerDigital::L2);
		tiltDirection = master.getDigital(ControllerDigital::R1) - master.getDigital(ControllerDigital::R2);
		liftDirection = buttonX.changedToPressed() - buttonB.changedToPressed();
		override = master.getDigital(ControllerDigital::Y);

        if(!override) {
	        if (tiltDirection)
		        tray::move_controlled(tiltDirection);
	        else {
		        intakeMotors.moveVelocity((int)intakeMotors.getGearing() * intakeDirection);
//		        if (liftDirection > 0) {
//			        if (liftState < 2)
//			        	++liftState;
//			        lift::setTarget(lift::state_to_pos(liftState));
//		        }
//		        else if(liftDirection<0){
//		        	if(liftState>0)
//		        		--liftState;
//			        lift::setTarget(lift::state_to_pos(liftState));
//		        }
//		        else {
//                    lift::move_controlled();
//
//		        }
                liftDirection = buttonX.isPressed() - buttonB.isPressed();
                if (liftDirection) {
                    lift::move_raw((int)transT.getGearing() * liftDirection);
                }
                else
                    hold_transmission_motors();
	        }
        }
        else{
	        intakeMotors.moveVelocity((int)intakeMotors.getGearing()*intakeDirection);
	        liftDirection = buttonX.isPressed() - buttonB.isPressed();
	        if (tiltDirection)
		        tray::move_raw((int)transT.getGearing()*tiltDirection);
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
		pros::lcd::print(1, "Tray: %lf", tray::get_pos_raw());
		pros::lcd::print(2, "Lift: %lf", lift::get_pos_raw());
		pros::lcd::print(3, "Lift state: %d", liftState);

		pros::delay(10);
    }
}
