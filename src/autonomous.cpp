
#include "main.h"
#include "robot/motors.h"
#include "robot/components/mechanisms.h"
#include "robot/robot.h"


/**
* Runs the user autonomous code. This function will be started in its own task
* with the default priority and stack size whenever the robot is enabled via
* the Field Management System or the VEX Competition Switch in the autonomous
* mode. Alternatively, this function may be called in initialize or opcontrol
* for non-competition testing purposes.
*
* If the robot is disabled or communications is lost, the autonomous task
* will be stopped. Re-enabling the robot will restart the task, not re-start it
* from where it left off.
*/

using namespace pros::c;

int flipout_sequence_index = 1;

void run_flipout_sequence()
{
    if (flipout_sequence_index >= 1 && flipout_sequence_index < 3)
    {
        if ((Mechanisms::trayP != nullptr && Mechanisms::trayP->finished()) || Mechanisms::trayP == nullptr)
        {
            if (flipout_sequence_index == 1)
                Mechanisms::set_tray_position(TRAY_POSITION_UP);
            else if (flipout_sequence_index == 2)
                Mechanisms::set_tray_position(TRAY_POSITION_DOWN);

            flipout_sequence_index++;
        }
        if (Mechanisms::trayP != nullptr && !Mechanisms::trayP->finished())
        {
            Mechanisms::trayP->update();
            Mechanisms::intake(-100);
        } else
        {
            Mechanisms::tilter(0);
            Mechanisms::intake(0);
        }
    }

    /*if(flipout_sequence_index >= 3)
    {
        if (((Mechanisms::liftP != nullptr && Mechanisms::liftP->finished()) || Mechanisms::liftP ==
                                                                                nullptr))
        {
            if (flipout_sequence_index == 3)
                Mechanisms::set_lift_position(LIFT_POSITION_UP);
            if (flipout_sequence_index == 4)
                Mechanisms::set_lift_position(LIFT_POSITION_DOWN);

            flipout_sequence_index++;
        }
        if (Mechanisms::liftP != nullptr && !Mechanisms::liftP->finished())
        {
            Mechanisms::liftP->update();
            Mechanisms::intake(-100);
        } else
        {
            Mechanisms::lifter(0);
            Mechanisms::intake(0);
        }
    }*/
}

void skills_run_setup()
{
    Auton::goto_pos(4.93, 7.92);
}
void skills_run_update()
{
    Robot::update();
    Mechanisms::intake(100);
}

void autonomous()
{
    Robot::robotMode = ROBOT_MODE_AUTON;
    Auton::goto_pos(0, 18);
    while (true)
    {
        Robot::update();
        run_flipout_sequence();
        delay(20);
    }
}
