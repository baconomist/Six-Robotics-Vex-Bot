#include "main.h"

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


pros::Motor iTrayLeft = pros::Motor(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor iTrayRight(5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

void initialize() {

	pros::lcd::initialize();
	pros::lcd::set_text(1, "  ____ ");
	pros::lcd::set_text(2, " / ___|");
	pros::lcd::set_text(3, "/ /__ ");
	pros::lcd::set_text(4, "| ___ \\ ");
	pros::lcd::set_text(5, "| \\_/ |");
	pros::lcd::set_text(6, "\\___/");

	pros::lcd::register_btn1_cb(on_center_button);
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	// master.rumble("- - ---");
	iTrayLeft.move_absolute(600, 200);
	iTrayRight.move_absolute(600, 200);
	
	driveLF.set_brake_mode(MOTOR_BRAKE_COAST);
    driveLB.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
    transB.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
