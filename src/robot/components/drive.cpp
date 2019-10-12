//
// Created by Lucas on 9/27/2019.
//
#include "main.h"
#include "drive.h"
#include "../motors.h"
#include "motor_gearsets.h"
#include "../controllers.h"

// TODO: refactor

/*
tank joystick control + strafe
*/
int scale(int speed,Motor motor){
  return speed * get_gearset_rpm(motor.get_gearing())/127.0f;
}
void Drive::tank()
{
  int deadZone = 15;
  int velLY = master.get_analog(ANALOG_LEFT_Y);
  int strafe = 127 * (master.get_digital(DIGITAL_RIGHT) - master.get_digital(DIGITAL_LEFT));
  int velRY = master.get_analog(ANALOG_RIGHT_Y);

  driveLB.move_velocity(velLY - strafe);
  driveLF.move_velocity(velLY + strafe);
  driveRB.move_velocity(velRY + strafe);
  driveRF.move_velocity(velRY - strafe);
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
  int velLY = scale(master.get_analog(ANALOG_LEFT_Y ), driveLB);
  int velRY = scale(master.get_analog(ANALOG_RIGHT_Y), driveLB);
  int velLX = scale(master.get_analog(ANALOG_LEFT_X ), driveLB);
  int velRX = scale(master.get_analog(ANALOG_RIGHT_Y), driveLB);



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

/*
uses 2 motors to control lift + tray
tray = transB(+-power) and transT(+- power)
lift = transB(+-power) and transT(-+ power)
*/


/*

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
  driveLF.set_brake_mode(MOTOR_BRAKE_COAST);
  driveLB.set_brake_mode(MOTOR_BRAKE_COAST);
  driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
  driveRF.set_brake_mode(MOTOR_BRAKE_COAST);
}
