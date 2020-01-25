//
// Created by Aryan Gajelli on 2020-01-22.
//

#include "main.h"
#ifndef _MECHANISMS_H_
#define _MECHANISMS_H_


namespace mechanisms {
	extern Motor transB;
	extern Motor transT;
	extern Potentiometer liftPot;
	extern Potentiometer trayPot;
	extern MotorGroup intakeMotors;

	void initialize();
	void hold_transmission_motors();

	namespace tray {
		/**
		 * @returns raw tray position
		 * */
		double get_tray_pos_raw();

		/**
		 * @returns remapped tray position between [0,1024]
		 * */
		double get_tray_pos();

		/**
		 * Moves the tray with no restrictions
		 * @warning DO NOT USE, UNLESS FOR OVERRIDE PURPOSES
		 * @param vel the velocity at which the tray will move
		 * */
		void move_tray_raw(int vel);

		/**
		 * Moves the tray at changing speeds to drop a stack while holding a button
		 * @param dir the direction in which the tray should move:
		 * 			  +ve means move up,
		 * 			  0 means dont move and hold current position,
		 * 			  -ve means move down		 *
		 * */
		void move_tray_controlled(int dir);

		/**
		 * Tray positions
		 * */
		enum trayPos{
			DOWN_POS = 1950,
			UP_POS = 10
		};


	}
	namespace lift {
		enum liftPos{
			DOWN_POS = 4000,
			MIDDLE_POS = 3000,
			UP_POS = 2000
		};

		void move_lift_raw(int vel);
	}
}
#endif //_MECHANISMS_H_
