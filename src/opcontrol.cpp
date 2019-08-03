#include "main.h"
//#include "okapi/api.hpp"

//using namespace okapi;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enablpred via
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

pros::Motor trayLeft(4, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor trayRight(5, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor frontLeftDrive(1, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor frontRightDrive(2, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backLeftDrive(9, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backRightDrive(10, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);



void opcontrol() {
    bool setting_up = true;
	pros::Controller master(pros::E_CONTROLLER_MASTER);
    trayLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    trayRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	while (true) {
        if ((trayLeft.get_position() >= 595) && (trayLeft.get_position() <= 605) && setting_up) {
    		trayLeft.move_absolute(0, 200);
    		trayRight.move_absolute(0, 200);
            setting_up = false;
    	}

		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

        trayLeft.move_velocity(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
        trayRight.move_velocity(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));


        // Mechanum drive
        int turn = master.get_analog(ANALOG_RIGHT_X);
        int forward = master.get_analog(ANALOG_RIGHT_Y);
        int sideways = 0;
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            sideways = -127;
            // Controller analog ranges from -127 to 127
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            sideways = 127;
        }

        int frontLeft = turn + forward + sideways;
        int backLeft = turn + forward - sideways;
        int frontRight = forward - turn - sideways;
        int backRight = turn - forward + sideways;

        frontLeftDrive.move_velocity(frontLeft * 100);
        backLeftDrive.move_velocity(backLeft * 100);
        frontRightDrive.move_velocity(frontRight * 100);
        backRightDrive.move_velocity(backRight * 100);

		pros::delay(20);
	}
}
