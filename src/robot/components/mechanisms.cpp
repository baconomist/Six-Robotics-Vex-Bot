#include "main.h"
#include "mechanisms.h"
#include "../controllers.h"
#include "../motors.h"
#include "../ports.h"
#include "../encoders.h"
#include "motor_gearsets.h"
#include "drive.h"
#include <cmath>

pros::Motor *transT;
pros::Motor *transB;
pros::Motor *intakeL;
pros::Motor *intakeR;

pros::ADIPotentiometer *trayPot;
pros::ADIPotentiometer *liftPot;
P *Mechanisms::trayP = nullptr;
P *Mechanisms::liftP = nullptr;

bool override; // "Shift" key to allow tray and lift to spin past the auto stop

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
    if (speed < 0 && get_tilter_pos() > 1970 && !override) {
        transB->move_velocity(0);
        transT->move_velocity(0);
    } else {
        transB->move_velocity(speed);
        transT->move_velocity(speed);
    }
}

float Mechanisms::get_tilter_pos() {
    return (float) trayPot->get_value();
}

/*
moves the lift up or down
*/
void Mechanisms::lifter(int speed) {
//    Mapping-based tray lift
//    if (get_tilter_pos() > 1900 || get_tilter_pos() < 1400) {
//        transB->move_velocity(-speed);
//    } else
//        transB->move_velocity(-speed * map(get_lift_pos(), 4000, 2800, 0.2, 0.6));

    if (get_lift_pos() < 4050 || speed > 0) {    // Make sure we can't break the tray when its at the bottom
        if (speed > 0 && get_tilter_pos() > 1850) {  // When the lift is going up and the tilter hasn't moved
            tilter(60);
        } else {
            if ((get_lift_pos() > 3000 && get_tilter_pos() > 1200) &&
                (get_lift_pos() < 3900 || speed < 0)) {   // If lift is up and the tray is down
                if (speed > 0)
                    transB->move_velocity(-speed * 0.1); // The lower the transB velocity, the faster the tray
                else if (speed < 0)
                    transB->move_velocity(-speed * 0.5);
                else {
                    transB->move_velocity(0);
                }
            } else
                transB->move_velocity(-speed);
            transT->move_velocity(speed);
        }

    } else {
        tilter(-60);
    }
}

float Mechanisms::get_lift_pos() {
    return (float) liftPot->get_value_calibrated();
}

/*
controls the intake
*/
void Mechanisms::intake(int speed) {
    speed = scale_motor_val(speed, intakeL);
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

void Mechanisms::initialize() {
    override = false;
    transT = new pros::Motor(TRANSMISSION_TOP, E_MOTOR_GEARSET_36, false);
    transB = new pros::Motor(TRANSMISSION_BOTTOM, E_MOTOR_GEARSET_36, true);//reversed
    intakeL = new pros::Motor(INTAKE_LEFT, E_MOTOR_GEARSET_18, false);
    intakeR = new pros::Motor(INTAKE_RIGHT, E_MOTOR_GEARSET_18, true);//reversed

    transT->set_brake_mode(MOTOR_BRAKE_HOLD);
    transB->set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeL->set_brake_mode(MOTOR_BRAKE_HOLD);
    intakeR->set_brake_mode(MOTOR_BRAKE_HOLD);

    trayPot = new pros::ADIPotentiometer(TRAY_POT);
    liftPot = new pros::ADIPotentiometer(LIFT_POT);

    liftPot->calibrate();
}

void Mechanisms::update() {
    // Button inputs
    int tilt = (master.get_digital(DIGITAL_R1)
                - master.get_digital(DIGITAL_R2));//slows down tilt speed as the tray goes up
    int lift = 100 * (master.get_digital(DIGITAL_X)
                      - master.get_digital(DIGITAL_B));
    int intakeSpeed = 100 * (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2));
    override = master.get_digital(DIGITAL_Y);

    // Brake if tray or lift is in use, otherwise coast
    if (get_tilter_pos() < 1650) {
        Drive::set_brake_all(MOTOR_BRAKE_HOLD);
    } else {
        Drive::set_brake_all(MOTOR_BRAKE_COAST);
    }

    if (tilt > 0) { // Tray going up
        tilter((int) map(get_tilter_pos(), 10, 1950, 8, 40, 2));
        intake((int) map(get_tilter_pos(), 10, 1950, -5, -30));
    } else {
        intake(intakeSpeed);
        if (tilt < 0) {     // Tray going down doesn't need to be smooth
            tilter(-60);
        } else if (override || lift > 0 || get_lift_pos() < 4040) {
            lifter(lift);
        } else {
            tilter(0);
            lifter(0);
        }
    }

    lcd::print(1, "Tray: %f", Mechanisms::get_tilter_pos());
    lcd::print(2, "Lift: %f", Mechanisms::get_lift_pos());
    lcd::print(3, "Power: %f", map(get_tilter_pos(), 10, 1950, 8, 40, 2));
}