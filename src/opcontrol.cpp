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
#include "robot/old/move_to_point.h"
#include "auton_editor_lib/auton_path_parser.h"

void opcontrol()
{
    Robot::robotMode = ROBOT_MODE_RC;
    Drive::driveMode = DRIVE_MODE_ARCADE;
    // robot->start_mainloop();

    //Robot::robotMode = ROBOT_MODE_AUTON;

    //initialize_mtp(20, 20);

    //Auton::goto_pos(0, 20);
    //Auton::goto_pos(0, -20);
    //Auton::goto_pos(20, 0);
    // Auton::goto_pos(20, 20);
    // Auton::goto_pos(20, 0);
    // Auton::goto_pos(0, 0);

    while (true)
    {
        Robot::update();
        //update_mtp();
        pros::delay(20);
    }

    //AutonPathParser *autonPathParser = new AutonPathParser(R"({"x":[[{"x_in":0,"y_in":0,"actions":[]},{"x_in":-48.08664259927798,"y_in":0.5198555956678632,"actions":[]},{"x_in":-49.64620938628159,"y_in":-36.90974729241877,"actions":[]}],[{"x_in":-23.263537906137174,"y_in":-0.2599277978339245},{"x_in":-48.086642599277965,"y_in":-18.714801444043317}]]})");
    //AutonPathParser *autonPathParser = new AutonPathParser(R"({"x":"y"})");
}
