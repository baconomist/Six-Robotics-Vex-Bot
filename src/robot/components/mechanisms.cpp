#include "main.h"
#include "mechanisms.h"
#include "../controllers.h"
#include "../motors.h"
#include "../ports.h"
#include "../encoders.h"
#include "motor_gearsets.h"
#include "drive.h"

pros::Motor *transT;
pros::Motor *transB;
pros::Motor *intakeL;
pros::Motor *intakeR;

//pros::ADIPotentiometer *trayPot;
//pros::ADIPotentiometer *liftPot;
//PD *Mechanisms::trayPD = nullptr;
//PD *Mechanisms::liftPD = nullptr;
//Task *Mechanisms::task = nullptr;

/*
moves the tray forwards and backwards
*/
void Mechanisms::tilter(int speed)
{
    transB->move_velocity(speed);
    transT->move_velocity(speed);
}

float Mechanisms::tilter_get_pos()
{
    return (float) trayPot->get_value_calibrated();
}

void Mechanisms::tilter_go_to_pos(const float *end)
{
//    trayPD = new PD(1.f, 1.f, tilter_get_pos, *end, [](float speed) {
//      tilter((int) speed);
//    });
//
//    while (!trayPD->finished()) {
//        trayPD->update();
//    }
}

/*
moves the lift up or down
*/
void Mechanisms::lifter(int speed)
{
    transB->move_velocity(-speed);
    transT->move_velocity(speed);
}

float Mechanisms::lift_get_pos()
{
    return (float) liftPot->get_value_calibrated();
}

void Mechanisms::lifter_go_to_pos(const float *end)
{
//    liftPD = new PD(1.f, 1.f, lift_get_pos, *end, [](float speed) {
//      lifter((int) speed);
//    });
//    while (liftPD->finished()) {
//        liftPD->update();
//    }
}

/*
controls the intake
*/
void Mechanisms::intake(int speed)
{
    intakeL->move_velocity(speed);
    intakeR->move_velocity(speed);
}

/*
initializes all the motor's brake states
*/
void Mechanisms::initialize()
{
    transT = new pros::Motor(TRANSMISSION_TOP, E_MOTOR_GEARSET_36, false);
    transB = new pros::Motor(TRANSMISSION_BOTTOM, E_MOTOR_GEARSET_36, true);//reversed
    intakeL = new pros::Motor(INTAKE_LEFT, E_MOTOR_GEARSET_36, false);
    intakeR = new pros::Motor(INTAKE_RIGHT, E_MOTOR_GEARSET_36, true);//reversed

    transT->set_brake_mode(MOTOR_BRAKE_HOLD);
    transB->set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeL->set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeR->set_brake_mode(MOTOR_BRAKE_HOLD);
//
//    trayPot = new pros::ADIPotentiometer(TRAY_POT);
//    liftPot = new pros::ADIPotentiometer(TRAY_POT);

}

bool Mechanisms::calibrate_sensors()
{
    trayPot->calibrate();
    liftPot->calibrate();
    pros::delay(500);
    return true;
}

/*

updates the motors action
*/
void Mechanisms::update()
{
    float tiltPoint;
    int tilt = 100 * (master.get_digital(DIGITAL_R1)
                      - master.get_digital(
            DIGITAL_R2));//sets tilit speed to 100 * the direction, scaled to match internal gearset
    int lift = 100 * (master.get_digital(DIGITAL_X)
                      - master.get_digital(
            DIGITAL_B));//sets lift speed to 100 * the direction, scaled to match internal gearset
    int intakeSpeed = 100 * (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2));


    if (tilt)
    {
        tilter(tilt);
        Drive::set_brake_all(MOTOR_BRAKE_HOLD);
    } else if (lift)
    {
        lifter(lift);
        Drive::set_brake_all(MOTOR_BRAKE_HOLD);
    } else
    {
        tilter(0);
        lifter(0);
        Drive::set_brake_all(MOTOR_BRAKE_COAST);
    }
    intake(intakeSpeed);

    //    if (master.get_digital(DIGITAL_A) && trayPD->finished()) {
    //
    //    } else if (!trayPD->finished()) {
    //        trayPD->update();
    //    }
}
