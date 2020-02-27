//
// Created by Aryan Gajelli on 2020-01-24.
//
#include "hardware.h"
#include "mechanisms.h"
#include "main.h"

using namespace hardware;
using namespace hardware::ports;

namespace mechanisms {
    Motor transB(transmission::BOTTOM * directions::transmission::BOTTOM);
    Motor transT(transmission::TOP * directions::transmission::TOP);
    Potentiometer liftPot(legacy::LIFT_POT);
    Potentiometer trayPot(legacy::TRAY_POT);

    MotorGroup intakeMotors{
            ports::intake::LEFT * directions::intake::LEFT,
            ports::intake::RIGHT * directions::intake::RIGHT
    };

    /**
     * Sets motor gearsets and brakemodes
     */
    void initialize() {
        transT.setGearing(AbstractMotor::gearset::red);
        transB.setGearing(AbstractMotor::gearset::red);
        intakeMotors.setGearing(AbstractMotor::gearset::green);

        transT.setBrakeMode(AbstractMotor::brakeMode::hold);
        transB.setBrakeMode(AbstractMotor::brakeMode::hold);
        intakeMotors.setBrakeMode(AbstractMotor::brakeMode::brake);

    }

    void hold_transmission_motors() {

        transT.moveVelocity(0);
        transB.moveVelocity(0);
    }

    namespace tray {

        double kP = 0.001;
        double kI = 0.00;
        double kD = 0.000025;
        IterativePosPIDController control = IterativeControllerFactory::posPID(kP, kI, kD);

        double get_pos_raw() {
            return trayPot.get();
        }

        void move_raw(int vel) {
            transB.moveVelocity(vel);
            transT.moveVelocity(vel);
        }

        void move_controlled(int dir, _Bool intakeOverride) {

            double tray_curr_pos = get_pos_raw();
            double slow_point = 1100;
            double intake_flip_point = 1300;
            int velocity;
            if (!dir || tray_curr_pos < trayPos::UP_POS && dir > 0 || tray_curr_pos > trayPos::DOWN_POS && dir < 0) {
                hold_transmission_motors();
            } else if (dir > 0) {
                /*
                 * Moves tray up while reducing speed slowly and then drastically slowing down in the end
                 * */
                if (tray_curr_pos >= slow_point) {
                    velocity = remapRange(
                            tray_curr_pos,
                            trayPos::DOWN_POS,
                            trayPos::UP_POS,
                            (int) transT.getGearing() * .65,
                            (int) transT.getGearing() * .17
                    );
                    move_raw(velocity);
                } else if (tray_curr_pos < slow_point) {
                    move_raw(19);

                }
                if (!intakeOverride)
                    if (tray_curr_pos >= intake_flip_point) {
                        intakeMotors.moveVelocity(-15);
                    } else if (tray_curr_pos < intake_flip_point) {
                        intakeMotors.moveVelocity(-20);
                    }
            } else if (dir < 0) {
                velocity = remapRange(
                        tray_curr_pos,
                        trayPos::DOWN_POS,
                        trayPos::UP_POS,
                        (int) transT.getGearing() * .5,
                        (int) transT.getGearing()
                );
                move_raw(-velocity);
            }
        }
    }

    namespace lift {
        double kP = 0.0011;
        double kI = 0.0001;
        double kD = 0.00001;
        IterativePosPIDController control = IterativeControllerFactory::posPID(kP, kI, kD,0.0001,std::make_unique<EKFFilter>(EKFFilter(0.00016)));


        double get_pos_raw() {
            return liftPot.get();
        }

        void move_raw(float vel) {
            transT.moveVelocity(vel);
            transB.moveVelocity(-vel);
        }

        void move_to(float pos_raw)
        {
            while(abs(get_pos_raw() - pos_raw) <= LIFT_ERROR){
                move_raw((int) transT.getGearing() * (lift::get_pos_raw() < pos_raw ? -1 : 1));
            }
            stop();
        }

        void stop()
        {
            move_raw(0);
        }

        liftPos state_to_pos(int state) {
            switch (state) {
                case 0:
                    return liftPos::DOWN_POS;
                case 1:
                    return liftPos::MIDDLE_POS;
                case 2:
                    return liftPos::UP_POS;
                default:
                    return liftPos::DOWN_POS;
            }
        }

        void setTarget(liftPos pos) {
            control.setTarget(pos);
        }

        bool move_controlled() {
            if (tray::get_pos_raw() < min_tray_pos_to_move_lift) {
                if (!control.isSettled()) {
                    double newInput = get_pos_raw();
                    double newOutput = control.step(newInput);
                    move_raw(-newOutput);
                }
            }
            return control.isSettled();
        }
    }
}
