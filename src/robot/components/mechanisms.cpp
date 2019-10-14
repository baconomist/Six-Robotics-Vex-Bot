#include "mechanisms.h"
#include "../controllers.h"
#include "../motors.h"

/*
moves the tray forwards and backwards
*/
void Mechanisms::tilter(int tilt){
    transB.move_velocity(tilt);//uses motor brake(hold) to prevent motor from turning
    transT.move_velocity(tilt);//rotates about transB
}
void Mechanisms::lifter(int lift){
    transB.move_velocity(-lift);
    transT.move_velocity(lift);
}

/*
controls the intake
*/
void Mechanisms::intake(int intakeSpeed) {
    intakeL.move_velocity(intakeSpeed);
    intakeR.move_velocity(intakeSpeed);
}

/*
initializes all the motor's brake states
*/
void Mechanisms::initialize(){
    transT.set_brake_mode(MOTOR_BRAKE_HOLD);
    transB.set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeL.set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeR.set_brake_mode(MOTOR_BRAKE_HOLD);
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


}
