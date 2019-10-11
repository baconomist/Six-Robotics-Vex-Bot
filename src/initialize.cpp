
#include "main.h"
#include "headers/motors.h"
#include "headers/motor_gearsets.h"
#include "main.h"
#include "headers/sensors.h"

// Motor* driveLB;
// Motor* driveLF;
// Motor* driveRB;
// Motor* driveRF;
// Motor* transB;
// Motor* transT;



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
  driveLF.set_brake_mode(MOTOR_BRAKE_COAST);
  driveLB.set_brake_mode(MOTOR_BRAKE_COAST);
  driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
  driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
  transB.set_brake_mode(MOTOR_BRAKE_HOLD);
  transB.set_brake_mode(MOTOR_BRAKE_HOLD);
  intakeL.set_brake_mode(MOTOR_BRAKE_HOLD);
  intakeR.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void initialize()
{
    setup_motors();

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
