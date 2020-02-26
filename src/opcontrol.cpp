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

float intakeDirection;
int tiltDirection;
int liftDirection;
int liftState = 0;
bool override;
bool liftMoving = false;
ControllerButton buttonX = ControllerButton(ControllerDigital::X);
ControllerButton buttonB = ControllerButton(ControllerDigital::B);
ControllerButton buttonA = ControllerButton(ControllerDigital::A);

/**
 * Driver control code, handles all RC input from controller
 */
void opcontrol() {


//    while(true) {
//        meccanumDrive->forward(1);
//        pros::delay(500);
//        meccanumDrive->stop();
//        pros::delay(250);
//        meccanumDrive->forward(-1);
//        pros::delay(500);
//        meccanumDrive->stop();
//        pros::delay(500);
//    }
//
//    chassisController->moveDistance(24_in);
//    chassisController->waitUntilSettled();
//
//    inertial::turnTo(90_deg);
//    chassisController->moveDistance(12_in);
//    inertial::turnTo(90_deg);
//    chassisController->moveDistance(12_in);
//    inertial::turnTo(90_deg);
//    chassisController->moveDistance(12_in);
//    inertial::turnTo(90_deg);
//
//    while (true) {
//        pros::lcd::print(1, "%f", inertial::imu.get_heading());
//        pros::delay(20);
//    }

    changeToDrive(DRIVE_FOUR_WHEEL);

    meccanumDrive->setBrakeMode(AbstractMotor::brakeMode::coast);

    lift::control.setTarget(lift::state_to_pos(liftState));
    lift::control.reset();

    //flipout();
    while (true) {
        // Make outtaking slower for towering
        intakeDirection = master.getDigital(ControllerDigital::L1) - 0.6 * master.getDigital(ControllerDigital::L2);
        tiltDirection = master.getDigital(ControllerDigital::R1) - master.getDigital(ControllerDigital::R2);
        liftDirection = (buttonX.changedToPressed() - buttonB.changedToPressed());
        override = master.getDigital(ControllerDigital::Y);
        if (tray::get_pos_raw() < 1700)
            meccanumDrive->setBrakeMode(AbstractMotor::brakeMode::hold);
        else
            meccanumDrive->setBrakeMode(AbstractMotor::brakeMode::coast);
        if (!override) {
            if (tiltDirection && lift::control.isSettled()) {
                tray::move_controlled(tiltDirection);
            } else if (liftDirection) {
                liftMoving = true;

                liftState +=
                        (liftState < 2 && liftDirection > 0) || (liftState > 0 && liftDirection < 0) ? liftDirection
                                                                                                     : 0;
                lift::control.setTarget(lift::state_to_pos(liftState));
                lift::control.reset();
            } else if (liftMoving) {

                if (tray::get_pos_raw() < lift::min_tray_pos_to_move_lift || lift::control.isSettled()) {
                    intakeMotors.moveVelocity((int) intakeMotors.getGearing() * intakeDirection);

                    lift::control.flipDisable(false);
                    if (!lift::control.isSettled()) {
                        // Lift PID iteration
                        double newOutput = lift::control.step(lift::get_pos_raw()) * (int) transT.getGearing();
                        lift::move_raw(-newOutput);
                    } else {
                        liftMoving = false;
                    }
                } else {  // Tray is too far down to move lift
                    intakeMotors.moveVelocity((int) intakeMotors.getGearing() * intakeDirection);
                    tray::move_raw(40);
                    lift::control.flipDisable(true);
                }
            } else {  // No desired tray or lift motion
                hold_transmission_motors();
                intakeMotors.moveVelocity((int) intakeMotors.getGearing() * intakeDirection);
            }
        } else {  // Override button pressed
            // Reset the lift PID so it doesn't try to continue after override
            lift::control.reset();


            intakeMotors.moveVelocity((int) intakeMotors.getGearing() * intakeDirection);

            liftDirection = buttonX.isPressed() - buttonB.isPressed();
            if (tiltDirection)
                tray::move_raw((int) transT.getGearing() * tiltDirection);
            else if (liftDirection) {
                lift::move_raw((int) transT.getGearing() * liftDirection);
            } else {
                hold_transmission_motors();
            }
        }

#define drivePow(joystick) (ipow(abs(master.getAnalog(joystick)), 2) * ((master.getAnalog(joystick)>0) - (master.getAnalog(joystick)<0)) )//* std::signbit(master.getAnalog(joystick))?-1:1)
        meccanumDrive->xArcade(
                drivePow(ControllerAnalog::rightX),
                drivePow(ControllerAnalog::leftY),
                drivePow(ControllerAnalog::leftX)
        );

        pros::lcd::print(1, "Lift Pos: %lf", lift::get_pos_raw());
        pros::lcd::print(2, "Tray Pos: %lf", tray::get_pos_raw());
        pros::lcd::print(3, "L Encoder: %lf", leftEncoder.get());
        pros::lcd::print(4, "R Encoder: %lf", rightEncoder.get());
        pros::lcd::print(5, "C Encoder: %lf", centerEncoder.get());

//        pros::lcd::print(3, "Lift Settled?: %d", lift::control.isSettled());

        pros::delay(10);
    }
}
