//
// Created by Aryan Gajelli on 2020-01-24.
//
#include "hardware.h"
#include "mechanisms.h"
#include "main.h"

using namespace hardware;
using namespace hardware::ports;

namespace mechanisms{
	Motor transB(transmission::BOTTOM * directions::transmission::BOTTOM);
	Motor transT(transmission::TOP * directions::transmission::TOP);

	Potentiometer liftPot(legacy::LIFT_POT);
	Potentiometer trayPot(legacy::TRAY_POT);

	MotorGroup intakeMotors{
		ports::intake::LEFT * directions::intake::LEFT,
		ports::intake::RIGHT * directions::intake::RIGHT
	};
	bool motor_lock = false;
	void initialize() {
		transT.setGearing(AbstractMotor::gearset::red);
		transB.setGearing(AbstractMotor::gearset::red);
		intakeMotors.setGearing(AbstractMotor::gearset::green);

		transT.setBrakeMode(AbstractMotor::brakeMode::hold);
		transB.setBrakeMode(AbstractMotor::brakeMode::hold);
		intakeMotors.setBrakeMode(AbstractMotor::brakeMode::brake);
	}
	namespace tray{
		double get_tray_pos_raw(){
			return trayPot.get();
		}
		double get_tray_pos(){
			return remapRange(get_tray_pos_raw(),trayPos::DOWN_POS,trayPos::UP_POS,0,100);
		}
		void move_tray_raw(int vel){
			transB.moveVelocity(vel);
			transT.moveVelocity(vel);
		}
		void move_tray_controlled(int vel){

		}
	}
	namespace lift{
		void move_lift_raw(int vel){
			transB.moveVelocity(vel);
			transT.moveVelocity(-vel);
		}

	}

}
