//
// Created by Lucas on 9/27/2019.
//
#include "main.h"
#include "robot/robot.h"
#include <stdarg.h>
#include "robot/motors.h"
#include "robot/ports.h"
#include "robot/controllers.h"
#include "robot/motion_control/PID.h"
#include "robot/components/move_to_point.h"
ADIPotentiometer tray(TRAY_POT);
ADIPotentiometer lift(LIFT_POT);
void opcontrol()
{
    robot->robotMode = REMOTE_CONTROLLED;
    // robot->start_mainloop();
    tray.calibrate();
    lift.calibrate();
    pros::delay(500);

    //initialize_mtp(20, 20);

    // Auton::goto_pos(0, 20);
    // Auton::goto_pos(20, 20);
    // Auton::goto_pos(20, 0);
    // Auton::goto_pos(0, 0);

    while (true)
    {
        robot->update();
        printf("%d %d\n",tray.get_value_calibrated_HR(),lift.get_value_calibrated_HR());
        //Auton::print_debug();
        //update_mtp();
        pros::delay(20);
    }
}
