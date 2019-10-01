//
// Created by Lucas on 9/27/2019.
//

#include <stdlib.h>

#include "main.h"

#include "drive.h"
#include "../motors.h"
#include "../../motor_gearsets.h"

// TODO: refactor

using namespace std;
using namespace pros;


Controller master(CONTROLLER_MASTER);

void Drive::tank()
{
    int deadZone = 15;
    int velLY = master.get_analog(ANALOG_LEFT_Y);
    int strafe = 90 * (master.get_digital(DIGITAL_RIGHT) - master.get_digital(DIGITAL_LEFT));
    int velRY = master.get_analog(ANALOG_RIGHT_Y);

    driveLB.move_velocity(velLY - strafe);
    driveLF.move_velocity(velLY + strafe);
    driveRB.move_velocity(velRY - strafe);
    driveRF.move_velocity(velRY + strafe);
}

void Drive::arcade()
{
    /*
    arcade joystick control + strafe
    */
    int deadZone = 15;//motors wont move if abs(joystick) is within this range
    int velLY = master.get_analog(ANALOG_LEFT_Y) * get_gearset_rpm(driveLB.get_gearing()) /
                127;//scaling the values to 200 to match the internal gearset for move_velocity
    int velRY = master.get_analog(ANALOG_RIGHT_Y) * get_gearset_rpm(driveRB.get_gearing()) / 127;//^^
    int velLX = master.get_analog(ANALOG_LEFT_X) * get_gearset_rpm(driveLB.get_gearing()) / 127;//^^
    int velRX = master.get_analog(ANALOG_RIGHT_X) * get_gearset_rpm(driveRB.get_gearing()) / 127;//^^


    if (abs(velLX) < deadZone && abs(velLY) > deadZone)
    {
        //drives straight if the Y dir is greater than dead zone and X dir is within dead zone
        driveLF.move_velocity(velLY + velRX);
        driveLB.move_velocity(velLY - velRX);
        driveRF.move_velocity(velLY - velRX);
        driveRB.move_velocity(velLY + velRX);
    } else if (abs(velLY) < deadZone && abs(velLX) > deadZone)
    {
        //turns on point if the X dir is greater than dead zone and Y dir is within dead zone
        driveLF.move_velocity(velLX + velRX);
        driveLB.move_velocity(velLX - velRX);
        driveRF.move_velocity(-velLX - velRX);
        driveRB.move_velocity(-velLX + velRX);
    } else
    {
        //arcade control + strafe
        driveLF.move_velocity(velLY - velLX + velRX);
        driveLB.move_velocity(velLY - velLX - velRX);
        driveRF.move_velocity(velLY + velLX - velRX);
        driveRB.move_velocity(velLY + velLX + velRX);
    }
}

void Drive::transmission()
{
    /*
    uses 2 motors to control lift + tray
    tray = transB(hold) and transT(+- power)
    lift = transB(+-power) and transT(-+ power)
    */
    int tilt = 100 * (master.get_digital(DIGITAL_R1) - master.get_digital(
            DIGITAL_R2));//sets tilit speed to 50 * the direction, scaled to match internal gearset
    int lift = 100 * (master.get_digital(DIGITAL_L1) - master.get_digital(
            DIGITAL_L2));//sets lift speed to 100 * the direction, scaled to match internal gearset
    if (tilt)
    {
        //moves the tray forwards and backwards
        transB.move_velocity(0);//uses motor brake(hold) to prevent motor from turning
        transT.move_velocity(-tilt);//rotates about transB
    } else if (lift)
    {
        //moves lift
        transB.move_velocity(-lift);
        transT.move_velocity(lift);
    } else
    {
        //holds the motors in the current postion
        transB.move_velocity(0);
        transT.move_velocity(0);
    }
}

void Drive::update()
{
    if (this->driveMode == TANK)
        tank();
    else if (this->driveMode == ARCADE)
        arcade();
}

