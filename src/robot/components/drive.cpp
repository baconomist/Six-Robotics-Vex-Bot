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

pros::Motor *driveLB;
pros::Motor *driveLF;
pros::Motor *driveRB;
pros::Motor *driveRF;


// TODO: refactor the arc_turn
/*
scales the motor value by the motors gearing
*/
int scale(int speed, Motor *motor)
{
    return speed * get_gearset_rpm(motor->get_gearing()) / 127.0f;
}

Drive::Drive() = default;

/*
moves the left side of the drive
\param speed
the scaled speed at which the left side of the drive will move
*/
void Drive::move_left(int speed)
{
    driveLB->move_velocity(speed);
    driveLF->move_velocity(speed);
}

/*
moves the right side of the drive
\param speed
the scaled speed at which the right side of the drive will move
*/
void Drive::move_right(int speed)
{
    driveLB->move_velocity(speed);
    driveLF->move_velocity(speed);
}

/*
drives straight either forwards or backwards
\param speed
the scaled speed at which the drive will move
*/
void Drive::move(int speed)
{
    move_left(speed);
    move_right(speed);
}

/*
turns on point around the center of mass
\param speed
the scaled speed at which the drive will turn
*/
void Drive::turn_on_point(int speed)
{
    move_left(speed);
    move_right(-speed);
}

/*
turns around an arc,
center is not the center of the robot/mass
*/
void Drive::arc_turn(float radians, float radius, int speed)
{
    move_left(radians / (2 * M_PI) * radius - Robot::WHEEL_TO_WHEEL_DIST);
    move_right(radians / (2 * M_PI) * radius + Robot::WHEEL_TO_WHEEL_DIST);
}

/*
strafes to the side
\param speed
the scaled speed at which the drive will strafe
*/
void Drive::strafe(int speed)
{
    driveLB->move_velocity(-speed);
    driveLF->move_velocity(speed);
    driveRB->move_velocity(speed);
    driveRF->move_velocity(-speed);
}

/*
tank joystick control + strafe
*/
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
    move_left(scale(velLY, driveLB));
    move_right(scale(velRY, driveLB));
    strafe(scale(velStrafe, driveLB));
}

/*
arcade joystick control + strafe
*/
void Drive::arcade()
{
    int deadZone = 15;//motors wont move if abs(joystick) is within this range
    /*
    scaling the values to 200 to match the internal gearset for move_velocity
    Since the all the motors on the drive have the same gearing anyone can be used to scale them
    */
    int velLY = scale(master.get_analog(ANALOG_LEFT_Y), driveLB);
    int velRY = scale(master.get_analog(ANALOG_RIGHT_Y), driveLB);
    int velLX = scale(master.get_analog(ANALOG_LEFT_X), driveLB);
    int velRX = scale(master.get_analog(ANALOG_RIGHT_X), driveLB);

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

float Drive::ticks_to_inches(float ticks)
{
    return (ticks / 360.0f) * Robot::WHEEL_DIAMETER * M_PI;
}

float Drive::inches_to_ticks(float inches)
{
    return (inches / (Robot::WHEEL_DIAMETER * M_PI)) * 360.0f;
}

void move_forward(float speed)
{
    driveLF->move_velocity((int) speed);
    driveLB->move_velocity((int) speed);
    driveRF->move_velocity((int) speed);
    driveRB->move_velocity((int) speed);
}

float get_bot_y_pos()
{
    return driveLF->get_position();
}

/*
updates the motors action
*/
void Drive::update()
{
    if (this->driveMode == TANK)
        tank();
    else if (this->driveMode == ARCADE)
        arcade();
}

/*
Initializes all motors to their brake settings
*/
void Drive::initialize()
{

    driveLF = new pros::Motor(LEFT_FRONT, E_MOTOR_GEARSET_18, false);
    driveLB = new pros::Motor(LEFT_BACK, E_MOTOR_GEARSET_18, false);
    driveRF = new pros::Motor(RIGHT_FRONT, E_MOTOR_GEARSET_18, true);//reserved
    driveRB = new pros::Motor(RIGHT_BACK, E_MOTOR_GEARSET_18, true);//reversed

    //pdInstance = new PD(0.5, 0.01, get_bot_y_pos, inches_to_ticks(24*4), move_forward);
    driveLF->set_encoder_units(MOTOR_ENCODER_DEGREES);
    driveRF->set_encoder_units(MOTOR_ENCODER_DEGREES);

    driveLF->set_brake_mode(MOTOR_BRAKE_COAST);
    driveLB->set_brake_mode(MOTOR_BRAKE_COAST);
    driveRF->set_brake_mode(MOTOR_BRAKE_COAST);
    driveRB->set_brake_mode(MOTOR_BRAKE_COAST);
}

void Drive::stop_motors()
{
    driveLF->move_velocity(0);
    driveLB->move_velocity(0);
    driveRF->move_velocity(0);
    driveRB->move_velocity(0);
}
