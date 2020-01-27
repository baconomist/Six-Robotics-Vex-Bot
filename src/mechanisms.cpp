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
		lift::control.setOutputLimits((int)transT.getGearing(), -(int)transT.getGearing());
//		lift::lift_async = std::dynamic_pointer_cast<AsyncPosPIDController>(AsyncPosControllerBuilder()
//			.withGearset(
//				{
//					AbstractMotor::gearset::red,
//					10.0 / 3.0
//				}
//			).withGains(
//				liftGains
//			).withMotor(
//				transT
//			).withMotor(
//				-1 * transmission::BOTTOM
//				* directions::transmission::BOTTOM // inverts the motor cuz we are running the lift
//			)
//			.build());

	}

	void hold_transmission_motors() {

		transT.moveVelocity(0);
		transB.moveVelocity(0);
	}
	namespace tray {

		double get_pos_raw() {
			return trayPot.get();
		}

		void move_raw(int vel) {
			transB.moveVelocity(vel);
			transT.moveVelocity(vel);
		}

		void move_controlled(int dir) {

			double tray_curr_pos = get_pos_raw();
			double slow_point = 1200;
			int velocity;
			if (!dir || tray_curr_pos < trayPos::UP_POS && dir > 0|| tray_curr_pos > trayPos::DOWN_POS && dir < 0) {
				hold_transmission_motors();
			}
			else if (dir > 0) {
				/*
				 * Moves tray up while reducing speed slowly and then drastically slowing down in the end
				 * */
				if (tray_curr_pos >= slow_point) {
					velocity = remapRange(
						tray_curr_pos,
						trayPos::DOWN_POS,
						trayPos::UP_POS,
						(int)transT.getGearing() * 0.7,
						(int)transT.getGearing() * .1
					);
					move_raw(velocity);
					intakeMotors.moveVelocity(20);
				}
				else if (tray_curr_pos < slow_point) {
					move_raw(10);
					intakeMotors.moveVelocity(-10);
				}
			}
			else if (dir < 0) {
				velocity = remapRange(
					tray_curr_pos,
					trayPos::DOWN_POS,
					trayPos::UP_POS,
					(int)transT.getGearing() * .5,
					(int)transT.getGearing()
				);
				move_raw(-velocity);
			}
		}
	}
	namespace lift {

		int min_tray_pos_to_move_lift = 1200;
		double kP = 0.01;
		double kI = 0.00;
		double kD = 0.00;
		IterativePosPIDController control = IterativeControllerFactory::posPID(kP, kI, kD);

		double get_pos_raw() {
			return liftPot.get();
		}

		void move_raw(int vel) {
			transT.moveVelocity(vel);
			transB.moveVelocity(-vel);
		}
		liftPos state_to_pos(int state){
			switch (state){
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
					move_raw(newOutput);
				}
			}
			return control.isSettled();

		}

	}

}
