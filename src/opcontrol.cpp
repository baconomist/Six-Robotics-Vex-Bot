
#include <algorithm>
#include <math.h>
#include "main.h"
#include "headers/motors.h"
#include "headers/controllers.h"
#include "headers/motor_gearsets.h"
#include "headers/ports.h"
#include "headers/sensors.h"

using namespace std;
/**
 * Scales the speed value to match the motors get_gearing
 * This function is to assist with the Motor::motor.move_velocity(int velocity) function
 */
int scale(int speed, Motor motor){
  double scaledSpeed = get_gearset_rpm(motor.get_gearing())/127.0;
  return speed * scaledSpeed;
}

void tank(){
  int deadZone = 15;
  int velLY = master.get_analog(ANALOG_LEFT_Y);
  int strafe = 90 * (master.get_digital(DIGITAL_RIGHT) - master.get_digital(DIGITAL_LEFT));
  int velRY = master.get_analog(ANALOG_RIGHT_Y);

  driveLB.move_velocity(velLY - strafe);
  driveLF.move_velocity(velLY + strafe);
  driveRB.move_velocity(velRY - strafe);
  driveRF.move_velocity(velRY + strafe);
}

/**
 * Arcade joystick control + strafe
 */
void arcade(){
  int deadZone = 15;//motors wont move if abs(joystick) is within this range
  int velLY = scale(master.get_analog(ANALOG_LEFT_Y), driveLB);//scaling the joystick values to 200 to match the internal gearset for move_velocity
  int velRY = scale(master.get_analog(ANALOG_RIGHT_Y),driveRB);//^^
  int velLX = scale(master.get_analog(ANALOG_LEFT_X), driveLB);//^^
  int velRX = scale(master.get_analog(ANALOG_RIGHT_X),driveRB);//^^

  if (abs(velLX) < deadZone && abs(velLY) > deadZone){
      //drives straight if the Y dir is greater than dead zone and X dir is within dead zone
      driveLF.move_velocity(velLY + velRX);
      driveLB.move_velocity(velLY - velRX);
      driveRF.move_velocity(velLY - velRX);
      driveRB.move_velocity(velLY + velRX);
  } else if (abs(velLY) < deadZone && abs(velLX) > deadZone){
      //turns on point if the X dir is greater than dead zone and Y dir is within dead zone
      driveLF.move_velocity(velLX + velRX);
      driveLB.move_velocity(velLX - velRX);
      driveRF.move_velocity(-velLX - velRX);
      driveRB.move_velocity(-velLX + velRX);
  } else {
      //arcade control + strafe
      driveLF.move_velocity(velLY - velLX + velRX);
      driveLB.move_velocity(velLY - velLX - velRX);
      driveRF.move_velocity(velLY + velLX - velRX);
      driveRB.move_velocity(velLY + velLX + velRX);
  }
}

/**
 * uses 2 motors to control lift + tray
 * tray = transB(+-) and transF(+- power)
 * lift = transB(+-power) and transF(-+ power)
 */
void transmission(){

    int tilt = 100 * (master.get_digital(DIGITAL_R1) - master.get_digital(
            DIGITAL_R2));//sets tilt speed to speed * the direction, scaled to match internal gearset
    int lift = 100 * (master.get_digital(DIGITAL_L1) - master.get_digital(
            DIGITAL_L2));//sets lift speed to 100 * the direction, scaled to match internal gearset
    if (tilt){
        //moves the tray forwards and backwards
        transB.move_velocity(tilt);//uses motor brake(hold) to prevent motor from turning
        transF.move_velocity(tilt);//rotates about transB
    } else if (lift){
        //moves lift
        transB.move_velocity(-lift);
        transF.move_velocity(lift);
    } else{
        //holds the motors in the current postion
        transB.move_velocity(0);
        transF.move_velocity(0);
    }
}

/*
  runs the intake in given direction
*/
void intake(){
  int speed = 100 * (master.get_digital(DIGITAL_UP) - master.get_digital(DIGITAL_DOWN));
  if(speed){
    intakeL.move_velocity(speed);
    intakeR.move_velocity(speed);
  }
  else{
    intakeL.move_velocity(0);
    intakeR.move_velocity(0);
  }
}
void opcontrol(){
    while (true){
      arcade();
      intake();
      transmission();
    }
}
