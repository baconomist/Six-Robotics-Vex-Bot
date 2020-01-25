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

		double get_tray_pos_raw() {
			return trayPot.get();
		}

		double get_tray_pos() {
			return remapRange(get_tray_pos_raw(), trayPos::DOWN_POS, trayPos::UP_POS, 0, 1024);
		}

		void move_tray_raw(int vel) {
			transB.moveVelocity(vel);
			transT.moveVelocity(vel);
		}

		void move_tray_controlled(int dir) {
			if (dir > 0) {
				double tray_curr_pos = get_tray_pos();
				double slow_point = 512;
				/*
				 * Moves tray up while reducing speed slowly and then drastically slowing down in the end
				 * */
				if(tray_curr_pos<=slow_point) {
					int velocity = remapRange(tray_curr_pos, 0, 1024, (int)transT.getGearing(), (int)transT.getGearing()/2);
					move_tray_raw(velocity);
				}
				else if(tray_curr_pos>slow_point){
					move_tray_raw(10);
				}
			}
			else if (dir < 0) {
				move_tray_raw(-(int)transT.getGearing());
			}
		}
	}
	namespace lift {

		void move_lift_raw(int vel) {
			transT.moveVelocity(-vel);
			transB.moveVelocity(vel);
		}

	}

}
