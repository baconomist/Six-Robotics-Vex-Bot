#include "mechanisms.h"
#include "../controllers.h"
#include "../motors.h"

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
    transB->move_velocity(speed);
    transT->move_velocity(-speed);
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

    transT->set_brake_mode(MOTOR_BRAKE_HOLD);
    transB->set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeL->set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeR->set_brake_mode(MOTOR_BRAKE_HOLD);
}

/*
updates the motors action
*/
void Mechanisms::update(){
    int tilt = 100 * (master.get_digital(DIGITAL_R1) - master.get_digital(DIGITAL_R2));//sets tilit speed to 100 * the direction, scaled to match internal gearset
    int lift = 100 * (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2));//sets lift speed to 100 * the direction, scaled to match internal gearset
    int intakeSpeed = 127 * (master.get_digital(DIGITAL_UP) - master.get_digital(DIGITAL_DOWN));
    if(tilt)
        tilter(tilt);
    else if(lift && !tilt)
        lifter(lift);
    else{
        tilter(0);
        lifter(0);
    }
    intake(intakeSpeed);
}
