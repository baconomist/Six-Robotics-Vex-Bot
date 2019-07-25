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
	while (true) {
        if ((trayLeft.get_position() >= 595) && (trayLeft.get_position() <= 605) && setting_up) {
    		trayLeft.move_absolute(0, 200);
    		trayRight.move_absolute(0, 200);
            setting_up = false;
    	}

		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

        // Mechanum drive
        int frontLeft = 0;
        int frontRight = 0;
        int backLeft = 0;
        int backRight = 0;

        int turn = master.get_analog(ANALOG_RIGHT_X);
        int forward = master.get_analog(ANALOG_LEFT_Y);
        int sideways = master.get_analog(ANALOG_LEFT_X);

        frontLeft = turn + forward + sideways;
        backLeft = turn + forward - sideways;
        frontRight = forward - turn - sideways;
        backRight = turn - forward + sideways;

        frontLeftDrive.move_velocity(frontLeft * 100);
        backLeftDrive.move_velocity(backLeft * 100);
        frontRightDrive.move_velocity(frontRight * 100);
        backRightDrive.move_velocity(backRight * 100);

		pros::delay(20);
	}
}
