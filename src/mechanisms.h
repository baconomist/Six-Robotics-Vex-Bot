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
		extern IterativePosPIDController control;

		/**
		 * @returns raw tray position
		 * */
		double get_pos_raw();

		/**
		 * Moves the tray with no restrictions
		 * @warning DO NOT USE, UNLESS FOR OVERRIDE PURPOSES
		 * @param vel The velocity at which the tray will move, from -gearsetRPM to +gearsetRPM
		 * */
		void move_raw(int vel);

		/**
		 * Moves the tray at changing speeds to drop a stack while holding a button
		 * @param dir The direction in which the tray should move:
		 * 			  +ve means move up,
		 * 			  0 means dont move and hold current position,
		 * 			  -ve means move down		 *
		 * */
		void move_controlled(int dir);

		/**
		 * Tray positions
		 * */
		enum trayPos {
			DOWN_POS = 1840,
			UP_POS = 10
		};
	}
	namespace lift {
		const int min_tray_pos_to_move_lift = 1500;
		extern IterativePosPIDController control;

		enum liftPos {
			DOWN_POS = 4070,
			MIDDLE_POS = 2700,
			UP_POS = 2550
		};

		/**
		 * @returns raw lift position, analogous to liftPot.get()
		 * */
		double get_pos_raw();

		/**
		 * Converts an int from [0,2] to lift positions
		 * @param state an integer in the range [0,2]
		 * @return liftPos corresponding with 'state'
		 * */
		liftPos state_to_pos(int state);

		/**
		 * Sets the target the lift should move to
		 * @param pos The position the lift should move to
		 * */
		void setTarget(liftPos pos);

		/**
		 * Moves the lift with no restrictions
		 * @warning DO NOT USE, UNLESS FOR OVERRIDE PURPOSES
		 * @param vel The velocity at which the tray will move, from -gearsetRPM to +gearsetRPM
		 * */
		void move_raw(int vel);

		/**
		 * Moves the lift while holding a button, moves tray out of the way as well
		 * @param dir the direction in which the lift should move:
		 * 			  +ve means move up,
		 * 			  0 means dont move and hold current position,
		 * 			  -ve means move down		 *
		 * */
		bool move_controlled();
	}
}
#endif //_MECHANISMS_H_
