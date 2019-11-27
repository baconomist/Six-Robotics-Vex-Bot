#include "main.h"
#include "mechanisms.h"
#include "../controllers.h"
#include "../motors.h"
#include "../ports.h"
#include "../motion_control/encoders.h"
#include "motor_gearsets.h"
pros::Motor *transT;
pros::Motor *transB;
pros::Motor *intakeL;
pros::Motor *intakeR;

pros::ADIEncoder *trayEncoder;

PD *Mechanisms::trayPD;

/*
moves the tray forwards and backwards
*/
void Mechanisms::tilter(int speed){
    transB->move_velocity(speed);
    transT->move_velocity(speed);
}

/*
moves the lift up or down
*/
void Mechanisms::lifter(int speed){
    transB->move_velocity(-speed);
    transT->move_velocity(speed);
}

/*
controls the intake
*/
void Mechanisms::intake(int speed) {
    intakeL->move_velocity(speed);
    intakeR->move_velocity(speed);
}

/*
initializes all the motor's brake states
*/
void Mechanisms::initialize(){
    transT = new pros::Motor(TRANSMISSION_TOP, E_MOTOR_GEARSET_36, false);
    transB = new pros::Motor(TRANSMISSION_BOTTOM, E_MOTOR_GEARSET_36, true);//reversed
    intakeL = new pros::Motor(INTAKE_LEFT, E_MOTOR_GEARSET_36, false);
    intakeR = new pros::Motor(INTAKE_RIGHT, E_MOTOR_GEARSET_36, true);//reversed

    transT->set_brake_mode(MOTOR_BRAKE_HOLD);
    transB->set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeL->set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeR->set_brake_mode(MOTOR_BRAKE_HOLD);

    trayEncoder = new pros::ADIEncoder(TRAY_ENCODER_TOP, TRAY_ENCODER_BOTTOM);
}

float Mechanisms::get_tray_pos()
{
  return (float)trayEncoder->get_value();
}
/*

updates the motors action
*/
void Mechanisms::update(){
    int tilt = 100 * (master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2));//sets tilit speed to 100 * the direction, scaled to match internal gearset
    int lift = 100 * (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2));//sets lift speed to 100 * the direction, scaled to match internal gearset
    int intakeSpeed = 100*(master.get_digital(DIGITAL_X) - master.get_digital(DIGITAL_B));
    if(tilt)
        tilter(tilt);
    else if(lift && !tilt)
        lifter(lift);
    else{
        tilter(0);
        lifter(0);
    }
    intake(intakeSpeed);

    if(master.get_digital(DIGITAL_A) && trayPD->finished()) {
        trayPD = new PD(1.f, 1.f, get_tray_pos, 40.f, [](float speed) {
          tilter((int)speed);
        });
    }
    else if(!trayPD->finished()) {
      trayPD->update();
    }
}
