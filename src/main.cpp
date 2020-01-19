#include "main.h"
#include "globals.h"

using namespace okapi;
using namespace hardware;
using namespace hardware::ports;

std::shared_ptr<OdomChassisController> chassisController;

okapi::MotorGroup intakeMotors {ports::intake::LEFT * directions::intake::LEFT, ports::intake::RIGHT * directions::intake::RIGHT};

okapi::Motor transB(transmission::BOTTOM * directions::transmission::BOTTOM);
okapi::Motor transT(transmission::TOP * directions::transmission::TOP);

okapi::Controller master;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();

	// Create global OdomChassisController
	okapi::ADIEncoder leftEncoder(legacy::LEFT_Y_ENCODER_TOP, legacy::LEFT_Y_ENCODER_BOTTOM);
	okapi::ADIEncoder rightEncoder(legacy::RIGHT_Y_ENCODER_BOTTOM, legacy::RIGHT_Y_ENCODER_TOP, false);
	okapi::ADIEncoder centerEncoder(legacy::X_ENCODER_BOTTOM, legacy::X_ENCODER_TOP, false);

	IterativePosPIDController::Gains distanceGains;
	distanceGains.kP = 0.0005;
	distanceGains.kI = 0;
	distanceGains.kD = 0.00000;

	IterativePosPIDController::Gains turnGains;
	turnGains.kP = 0.0005;
	turnGains.kI = 0;
	turnGains.kD = 0.00000;

	IterativePosPIDController::Gains angleGains;
	angleGains.kP = 0.0005;
	angleGains.kI = 0;
	angleGains.kD = 0.00000;

	chassisController = ChassisControllerBuilder()
		.withMotors(drive::LEFT_FRONT,
			directions::drive::RIGHT_FRONT * drive::RIGHT_FRONT, directions::drive::RIGHT_BACK * drive::RIGHT_BACK, drive::LEFT_BACK)
		.withSensors(
			leftEncoder,
			rightEncoder,
			centerEncoder
		)
		.withGains(distanceGains, turnGains, angleGains)
		.withDimensions(okapi::AbstractMotor::gearset::green, {{ 3.25_in, 16_in }, okapi::imev5GreenTPR })
		.withOdometry({{ 3.25_in, 16_in }, okapi::quadEncoderTPR }, StateMode::CARTESIAN)
		.buildOdometry();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
}