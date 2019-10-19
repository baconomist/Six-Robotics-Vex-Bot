
#include "main.h"
#include "robot/robot.h"

Robot *robot;

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

void initialize()
{
    pros::lcd::initialize();
    robot = new Robot(4.125, 23.0, 23.0);
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
