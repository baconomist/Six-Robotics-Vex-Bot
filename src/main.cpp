#include "main.h"
#include "globals.h"

using namespace okapi;
using namespace hardware;
using namespace hardware::ports;

std::shared_ptr<OdomChassisController> chassisController;

MotorGroup intakeMotors {ports::intake::LEFT * directions::intake::LEFT, ports::intake::RIGHT * directions::intake::RIGHT};

Motor transB(transmission::BOTTOM * directions::transmission::BOTTOM);
Motor transT(transmission::TOP * directions::transmission::TOP);

Controller master;

/**
 * Builds the chassisController
 */
void initializeDrive()
{
	ADIEncoder leftEncoder(legacy::LEFT_Y_ENCODER_TOP, legacy::LEFT_Y_ENCODER_BOTTOM);
	ADIEncoder rightEncoder(legacy::RIGHT_Y_ENCODER_BOTTOM, legacy::RIGHT_Y_ENCODER_TOP, false);
	ADIEncoder centerEncoder(legacy::X_ENCODER_BOTTOM, legacy::X_ENCODER_TOP, false);

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
		.withMotors(
			drive::LEFT_FRONT,
			directions::drive::RIGHT_FRONT * drive::RIGHT_FRONT,
			directions::drive::RIGHT_BACK * drive::RIGHT_BACK,
			drive::LEFT_BACK
		)
		.withSensors(
			leftEncoder,
			rightEncoder,
			centerEncoder
		)
		.withGains(
			distanceGains,
			turnGains,
			angleGains
		)
		.withOdometry(
			{
				//dimensions and layout of encoders
				{
					3.25_in,	//encoder wheel diameter
					12_in,		//center to center dist. of l and R encoders
					5_in,		//dist. between middle encoder and center of bot //TODO: change this value to be accurate, it is currently not measured
					3.25_in		//middle encoder wheel diameter
				},
				quadEncoderTPR	//ticks per rotation of encoder
			},
			StateMode::CARTESIAN
		)
		.buildOdometry();
}

void initializeMechanisms()
{
	transB.setBrakeMode(AbstractMotor::brakeMode::hold);
	transT.setBrakeMode(AbstractMotor::brakeMode::hold);
	intakeMotors.setBrakeMode(AbstractMotor::brakeMode::hold);
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	initializeDrive();
	initializeMechanisms();
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
