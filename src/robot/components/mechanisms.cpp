#include "mechanisms.h"
#include "../controllers.h"
#include "../motors.h"

void Mechanisms::transmission()
{
  int tilt = 100 * (master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2));//sets tilit speed to 100 * the direction, scaled to match internal gearset
  int lift = 100 * (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2));//sets lift speed to 100 * the direction, scaled to match internal gearset
  if (tilt)
  {
    //moves the tray forwards and backwards
    transB.move_velocity(tilt);//uses motor brake(hold) to prevent motor from turning
    transT.move_velocity(tilt);//rotates about transB
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

/*
controls the intake
*/
void Mechanisms::intake() {
  int intakeSpeed = 127 * (master.get_digital(DIGITAL_UP) - master.get_digital(DIGITAL_DOWN));
  intakeL.move_velocity(intakeSpeed);
  intakeR.move_velocity(intakeSpeed);
}

void Mechanisms::initialize(){
  transT.set_brake_mode(MOTOR_BRAKE_HOLD);
  transB.set_brake_mode(MOTOR_BRAKE_HOLD);
  intakeL.set_brake_mode(MOTOR_BRAKE_HOLD);
  intakeR.set_brake_mode(MOTOR_BRAKE_HOLD);
}
void Mechanisms::update(){
  intake();
  transmission();
}
