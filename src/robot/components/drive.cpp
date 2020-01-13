//
// Created by Lucas on 9/27/2019.
//
#include "../robot.h"
#include "main.h"
#include "drive.h"
#include "../motors.h"
#include "motor_gearsets.h"
#include "../controllers.h"
#include "../motion_control/PID.h"
#include "../ports.h"
#include <cmath>

DriveMode Drive::driveMode = DRIVE_MODE_TANK;

DriveMode Drive::driveMode = DRIVE_MODE_TANK;

const float TTI = Robot::TRACKING_WHEEL_DIAMETER / 360.0 * M_PI;
const float ITT = 1.0 / TTI;

pros::Motor *driveLB;
pros::Motor *driveLF;
pros::Motor *driveRB;
pros::Motor *driveRF;

// float power(int val, int p, Motor motor, int deadzone = 0){
//     float max_speed = get_gearset_rpm(motor.get_gearing());
//     return ((val>0)-(val<0)) * powf((abs(val)-deadzone)/max_speed,p)*max_speed;
// }

//P *rotateLeftPID;
//P *rotateRightPID;

DriveMode driveMode = DRIVE_MODE_ARCADE;

/*
maps the value from the range [curr_min, curr_max] to a value in the range [tar_min, tar_max]
and scales it depending on the power
*/

float map(float val, float curr_min, float curr_max, float tar_min, float tar_max, int power) {
    int sgn = (val>0) - (val<0);
    float x = (fabsf(val) - curr_min)*(tar_max - tar_min)/(curr_max - curr_min);
    return fabsf(val) <=curr_min? 0:(tar_min + (power > 1 ? (float) pow((x)/(tar_max - tar_min), power - 1)*x : x))*sgn;
    // y = ax^2 + bx + c
}
int scale_motor_val(int speed, Motor *motor,  int deadzone = 0, int p = 1)
{
    return ((speed > 0) - (speed < 0)) * powf((abs(speed) - deadzone) / 127, p) *
           get_gearset_rpm(motor->get_gearing()) * 127;
}

/**
 * Moves the left side of the drive
 * **/
void Drive::move_left(float speed)
{
    driveLF->move_velocity((int) speed);
    driveLB->move_velocity((int) speed);
}

/**
 * Moves the right side of the drive
 * **/
void Drive::move_right(float speed)
{
    driveRF->move_velocity((int) speed);
    driveRB->move_velocity((int) speed);
}

/**
 * Moves the left and right side of the drive
 * at the given speed parameter
 * **/
void Drive::move_straight(float speed)
{
    Drive::move_left(speed);
    Drive::move_right(speed);
}

/**
 * Turns the drive by setting left and right
 * side to opposite values
 * **/
void Drive::turn(float speed)
{
    move_left(speed);
    move_right(-speed);
}

/**
 * Strafes the drive
 * **/
void Drive::strafe(int speed)
{
    driveLB->move_velocity(-speed);
    driveLF->move_velocity(speed);
    driveRB->move_velocity(speed);
    driveRF->move_velocity(-speed);
}


void Drive::stop()
{
    move_left(0);
    move_right(0);
}

/**
 * Runs tank control scheme
 * **/
void Drive::tank()
{
    int deadZone = 15;
    int velLY = master.get_analog(ANALOG_LEFT_Y);
    int velStrafe = 127 * (master.get_digital(DIGITAL_RIGHT) - master.get_digital(DIGITAL_LEFT));
    int velRY = master.get_analog(ANALOG_RIGHT_Y);
    // driveLB->move_velocity(velLY - strafe);
    // driveLF->move_velocity(velLY + strafe);
    // driveRB->move_velocity(velRY + strafe);
    // driveRF->move_velocity(velRY - strafe);

    // scale all velocities to Left-Back drive(all drives will be same gearset)
    move_left(scale_motor_val(velLY, driveLB));
    move_right(scale_motor_val(velRY, driveLB));
    strafe(scale_motor_val(velStrafe, driveLB));
}

/**
 * Runs arcade control scheme
 * **/
void Drive::arcade()
{
    int deadZone = 15;//motors wont move if abs(joystick) is within this range
    /*
    scaling the values to 200 to match the internal gearset for move_velocity
    Since the all the motors on the drive have the same gearing anyone can be used to scale them
    */
    int velLY = map(master.get_analog(ANALOG_LEFT_Y),deadZone,127,0, get_gearset_rpm(driveLB->get_gearing()),2);
    // int velRY = map(master.get_analog(ANALOG_RIGHT_Y),deadZone,127,0, get_gearset_rpm(driveLB->get_gearing()),2);
    int velLX = map(master.get_analog(ANALOG_LEFT_X),deadZone,127,0, get_gearset_rpm(driveLB->get_gearing()),2);
    int velRX = map(master.get_analog(ANALOG_RIGHT_X),deadZone,127,0, get_gearset_rpm(driveLB->get_gearing()),2);

    if (abs(velLX) < deadZone && abs(velLY) > deadZone)
    {
        //drives straight if the Y dir is greater than dead zone and X dir is within dead zone
        driveLF->move_velocity(velLY + velRX);
        driveLB->move_velocity(velLY - velRX);
        driveRF->move_velocity(velLY - velRX);
        driveRB->move_velocity(velLY + velRX);
    } else if (abs(velLY) < deadZone && abs(velLX) > deadZone)
    {
        //turns on point if the X dir is greater than dead zone and Y dir is within dead zone
        driveLF->move_velocity(velLX + velRX);
        driveLB->move_velocity(velLX - velRX);
        driveRF->move_velocity(-velLX - velRX);
        driveRB->move_velocity(-velLX + velRX);
    } else
    {
        //arcade control + strafe
        driveLF->move_velocity(velLY + velLX + velRX);
        driveLB->move_velocity(velLY + velLX - velRX);
        driveRF->move_velocity(velLY - velLX - velRX);
        driveRB->move_velocity(velLY - velLX + velRX);
    }
}

void Drive::arcade2()
{
    int deadZone = 15;//motors wont move if abs(joystick) is within this range
    /*
    scaling the values to 200 to match the internal gearset for move_velocity
    Since the all the motors on the drive have the same gearing anyone can be used to scale them
    */
    int velLY = scale_motor_val(master.get_analog(ANALOG_LEFT_Y), driveLB);
    int velRY = scale_motor_val(master.get_analog(ANALOG_RIGHT_Y), driveLB);
    int velLX = scale_motor_val(master.get_analog(ANALOG_LEFT_X), driveLB);
    int velRX = scale_motor_val(master.get_analog(ANALOG_RIGHT_X), driveLB);

    if (abs(velLX) < deadZone && abs(velLY) > deadZone)
    {
        //drives straight if the Y dir is greater than dead zone and X dir is within dead zone
        driveLF->move_velocity(velLY + velRX);
        driveLB->move_velocity(velLY - velRX);
        driveRF->move_velocity(velLY - velRX);
        driveRB->move_velocity(velLY + velRX);
    } else if (abs(velLY) < deadZone && abs(velLX) > deadZone)
    {
        //turns on point if the X dir is greater than dead zone and Y dir is within dead zone
        driveLF->move_velocity(velLX + velRX);
        driveLB->move_velocity(velLX - velRX);
        driveRF->move_velocity(-velLX - velRX);
        driveRB->move_velocity(-velLX + velRX);
    } else
    {
        //arcade control + strafe
        driveLF->move_velocity(velLY + velLX + velRX);
        driveLB->move_velocity(velLY + velLX - velRX);
        driveRF->move_velocity(velLY - velLX - velRX);
        driveRB->move_velocity(velLY - velLX + velRX);
    }
}


/*
updates the motors action
*/
void Drive::update()
{
//    rotateLeftPID->update();
//    rotateRightPID->update();

    //if (rotateRightPID->finished());
    //    stop_motors();

    if (driveMode == DRIVE_MODE_TANK)
        tank();
    else if (driveMode == DRIVE_MODE_ARCADE)
        arcade();
}

/*
Initializes all motors to their brake settings
*/
void Drive::initialize()
{

    driveLF = new pros::Motor(LEFT_FRONT, MOTOR_GEARSET_GREEN, false);
    driveLB = new pros::Motor(LEFT_BACK, MOTOR_GEARSET_GREEN, false);
    driveRB = new pros::Motor(RIGHT_BACK, MOTOR_GEARSET_GREEN, true);//reversed
    driveRF = new pros::Motor(RIGHT_FRONT, MOTOR_GEARSET_GREEN, true);//reserved

    //
    // float degrees = 360;
    // float arc_center = 7.75f*2;
    // // Distance from center of robot to corresponding side
    // float l = arc_center + Robot::WHEEL_TO_CENTER_DIST;
    // float r = arc_center - Robot::WHEEL_TO_CENTER_DIST;
    //
    // float deltaL = (degrees * (M_PI / 180)) * l;
    // float deltaR = (degrees * (M_PI / 180)) * r;
    // rotateLeftPID = new P(0.5, get_bot_l_pos, inches_to_ticks(deltaL), move_left);
    // rotateRightPID = new P(0.5 * (r / l), get_bot_r_pos, inches_to_ticks(deltaR), move_right);
    // pros::lcd::print(5, "deltaL start: %f deltaR start: %f", deltaL, deltaR);

    driveLF->set_encoder_units(MOTOR_ENCODER_DEGREES);
    driveRF->set_encoder_units(MOTOR_ENCODER_DEGREES);
    driveLB->set_encoder_units(MOTOR_ENCODER_DEGREES);
    driveRB->set_encoder_units(MOTOR_ENCODER_DEGREES);

    set_brake_all(MOTOR_BRAKE_COAST);

}


void Drive::set_brake_all(motor_brake_mode_e brake_mode)
{
    driveLF->set_brake_mode(brake_mode);
    driveLB->set_brake_mode(brake_mode);
    driveRF->set_brake_mode(brake_mode);
    driveRB->set_brake_mode(brake_mode);
}
