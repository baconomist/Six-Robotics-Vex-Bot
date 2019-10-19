//
// Created by Lucas on 9/27/2019.
//
#include "main.h"
#include "robot/robot.h"
#include <stdarg.h>
#include "robot/motors.h"
#include "robot/controllers.h"
#include "robot/motion_control/PID.h"

void opcontrol()
{
    robot->robotMode = REMOTE_CONTROLLED;
    // robot->start_mainloop();

    while (true)
    {
        //robot->update();

        if(master.get_digital(DIGITAL_Y))
            robot->update();
        else
        {
            robot->drive->stop_motors();
        }

        pros::lcd::print(0, "Kp: %f", Kp);
        pros::lcd::print(1, "Ki: %f", Ki);
        pros::lcd::print(2, "Kd: %f", Kd);

        if(master.get_digital(DIGITAL_R1))
            Kd = 0;

        if(master.get_digital(DIGITAL_UP))
            Kp += 0.0001;
        else if(master.get_digital(DIGITAL_DOWN))
            Kp -= 0.0001;

        if(master.get_digital(DIGITAL_L1))
            Ki += 0.0001;
        else if(master.get_digital(DIGITAL_L2))
            Ki -= 0.0001;

        if(master.get_digital(DIGITAL_RIGHT))
            Kd += 0.0001;
        else if(master.get_digital(DIGITAL_LEFT))
            Kd -= 0.0001;

        Kp += 0.001*master.get_analog(ANALOG_LEFT_X);
        Kd += 0.001*master.get_analog(ANALOG_RIGHT_Y);

        if (master.get_digital(DIGITAL_X))
            driveLF->tare_position();

        pros::delay(20);
    }
}
