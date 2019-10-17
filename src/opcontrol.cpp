//
// Created by Lucas on 9/27/2019.
//
#include "main.h"
#include "robot/robot.h"
#include <stdarg.h>
#include "robot/controllers.h"
#include "robot/motion_control/PID.h"
void opcontrol()
{
    robot->robotMode = REMOTE_CONTROLLED;
    // robot->start_mainloop();
    char buffer[20];
    while(true){
        robot->update();
        sprintf(buffer,"%f",Kp);
        master.set_text(0, 0, buffer);
        Kp+=0.00001*(master.get_digital(DIGITAL_Y)-master.get_digital(DIGITAL_A));
    }
}
