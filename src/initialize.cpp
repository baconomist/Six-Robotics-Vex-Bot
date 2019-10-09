
#include "main.h"
#include "robot/robot.h"

#include "robot/motors.h"
#include "motor_gearsets.h"
#include "main.h"
#include "encoders.h"
#include "ports.h"

// Motor* driveLB;
// Motor* driveLF;
// Motor* driveRB;
// Motor* driveRF;
// Motor* transB;
// Motor* transT;

pros::ADIEncoder LeftXEncoder(LEFT_X_ENCODER_TOP, LEFT_X_ENCODER_BOTTOM);
pros::ADIEncoder RightXEncoder(RIGHT_X_ENCODER_TOP, RIGHT_X_ENCODER_BOTTOM);
pros::ADIEncoder YEncoder(Y_ENCODER_TOP, Y_ENCODER_BOTTOM);

Robot* robot;

void on_center_button()
{
    static bool pressed = false;
    pressed = !pressed;
    if (pressed)
    {
        lcd::set_text(2, "I was pressed!");
    } else
    {
        lcd::clear_line(2);
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void setup_motors()
{

    // driveLF = new pros::Motor(LEFT_FRONT, MOTOR_GEARSET_GREEN, false, E_MOTOR_ENCODER_DEGREES);
    // driveLB = new pros::Motor(LEFT_BACK, MOTOR_GEARSET_GREEN, false, E_MOTOR_ENCODER_DEGREES);
    // driveRF = new pros::Motor(RIGHT_FRONT, MOTOR_GEARSET_GREEN, true, E_MOTOR_ENCODER_DEGREES);//reserved
    // driveRB = new pros::Motor(RIGHT_BACK, MOTOR_GEARSET_GREEN, true, E_MOTOR_ENCODER_DEGREES);//reversed
    // transT = new pros::Motor(TRANSMISSION_TOP, MOTOR_GEARSET_RED, false, E_MOTOR_ENCODER_DEGREES);
    // transB = new pros::Motor(TRANSMISSION_BOTTOM, MOTOR_GEARSET_RED, true, E_MOTOR_ENCODER_DEGREES);//reversed


    driveLF.set_brake_mode(MOTOR_BRAKE_COAST);
    driveLB.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
    driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
    transB.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void initialize()
{
    robot = new Robot();

    setup_motors();
    robot->initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{}

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
{}
