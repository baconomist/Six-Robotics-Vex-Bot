#include "main.h"
#include "mechanisms.h"
#include "../controllers.h"
#include "../motors.h"
#include "../ports.h"
#include "../encoders.h"
#include "motor_gearsets.h"
#include "drive.h"
#include <cmath>

using namespace std;
pros::Motor *transT;
pros::Motor *transB;
pros::Motor *intakeL;
pros::Motor *intakeR;

pros::ADIPotentiometer *trayPot;
pros::ADIPotentiometer *liftPot;
P *Mechanisms::trayP = nullptr;
P *Mechanisms::liftP = nullptr;


/*
maps the value from the range [curr_min, curr_max] to a value in the range [tar_min, tar_max]
and scales it depending on the power
*/
float map(float val, float curr_min, float curr_max, float tar_min, float tar_max, int power = 1) {
    float x = (val - curr_min) * (tar_max - tar_min) / (curr_max - curr_min);
    return tar_min + (power > 1 ? x * (float) pow(x / (tar_max - tar_min), power - 1) : x);
    // y = ax^2 + bx + c
}

/*
moves the tray forwards and backwards
*/
void Mechanisms::tilter(int speed) {
    transB->move_velocity(speed);
    transT->move_velocity(speed);
}

float Mechanisms::get_tilter_pos() {
    return (float) trayPot->get_value();
}

/*
moves the lift up or down
*/
void Mechanisms::lifter(int speed) {
    transB->move_velocity(-speed);
    transT->move_velocity(speed);
}

float Mechanisms::get_lift_pos() {
    return (float) liftPot->get_value();
}

/*
controls the intake
*/
void Mechanisms::intake(int speed) {
    intakeL->move_velocity(speed);
    intakeR->move_velocity(speed);
}

void Mechanisms::set_tray_position(TrayPosition trayPosition) {
    if (trayPosition == TRAY_POSITION_UP)
        trayP = new P(0.5f, get_tilter_pos, 10, [](float speed) { tilter(-(int) speed); }, 100);
    else if (trayPosition == TRAY_POSITION_DOWN)
        trayP = new P(0.5f, get_tilter_pos, 1950, [](float speed) { tilter(-(int) speed); }, 100);
}

void Mechanisms::set_lift_position(LiftPosition liftPosition) {
    if (liftPosition == LIFT_POSITION_UP)
        liftP = new P(0.5f, get_lift_pos, 2900, [](float speed) { lifter(-(int) speed); }, 100);
    else if (liftPosition == LIFT_POSITION_MIDDLE)
        liftP = new P(0.5f, get_lift_pos, 3200, [](float speed) { lifter(-(int) speed); }, 100);
    else if (liftPosition == LIFT_POSITION_DOWN)
        liftP = new P(10.0f, get_lift_pos, 3850, [](float speed) { lifter(-(int) speed); }, 100);
}

/*
initializes all the motor's brake states
*/
void Mechanisms::initialize() {
    transT = new pros::Motor(TRANSMISSION_TOP, E_MOTOR_GEARSET_36, false);
    transB = new pros::Motor(TRANSMISSION_BOTTOM, E_MOTOR_GEARSET_36, true);//reversed
    intakeL = new pros::Motor(INTAKE_LEFT, E_MOTOR_GEARSET_36, false);
    intakeR = new pros::Motor(INTAKE_RIGHT, E_MOTOR_GEARSET_36, true);//reversed

    transT->set_brake_mode(MOTOR_BRAKE_HOLD);
    transB->set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeL->set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeR->set_brake_mode(MOTOR_BRAKE_HOLD);

    trayPot = new pros::ADIPotentiometer(TRAY_POT);
    liftPot = new pros::ADIPotentiometer(LIFT_POT);
//    trayPot->calibrate();
//    liftPot->calibrate();
//    //trayPD = new PD(0.1, 0.1, tilter_get_pos, 0, [](float speed) { tilter(speed); }, true);
//
//    trayPot->calibrate();
//    liftPot->calibrate();
}

/*
updates the motors action
*/
int liftState = 0;

void Mechanisms::update() {
    int tilt = (master.get_digital(DIGITAL_R1)
                - master.get_digital(DIGITAL_R2));//slows down tilt speed as the tray goes up
    int lift = 100 * (master.get_digital(DIGITAL_X)
                      - master.get_digital(DIGITAL_B));
    int intakeSpeed = 100 * (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2));



    // Brake if tray or lift is in use, otherwise coast
    if (get_tilter_pos() < 1650) {
        Drive::set_brake_all(MOTOR_BRAKE_HOLD);
    } else {
        Drive::set_brake_all(MOTOR_BRAKE_COAST);
    }

    if (tilt > 0) {
        tilter((int) map(get_tilter_pos(), 10, 1950, 8, 40, 2));
        intake(-5);
    } else {
        intake(intakeSpeed);
        if (tilt < 0) {
            tilter(-60);
        } else if (lift && get_tilter_pos() < 1700) // Tray must move out of way to allow lift
        {
            lifter(lift);
        } else {
            tilter(0);
            lifter(0);
        }
    }


    lcd::print(1, "Tray: %f", Mechanisms::get_tilter_pos());
    lcd::print(2, "Lift: %f", Mechanisms::get_lift_pos());
    lcd::print(3, "Power: %f", map(get_tilter_pos(), 10, 1950, 8, 40, 2));
    /* // Lift flipout automation
     if (flipout_sequence_index >= 1 && trayP->finished())
     {
         if (flipout_sequence_index == 2)
             liftP = new P(0.1f, get_lift_pos, INSERT_LIFT_MID_VAL_HERE, [](float speed) { tilter((int) speed); }, 100);
         else if (flipout_sequence_index == 3)
             liftP = new P(0.5f, get_lift_pos, INSERT_LIFT_BOTTOM_VAL_HERE, [](float speed) { tilter((int) speed); }, 100);
         flipout_sequence_index++;
     }
     if (liftP != nullptr && !liftP->finished())
     {
         liftP->update();
     } else
     {
         lifter(0);
     }*/
}
