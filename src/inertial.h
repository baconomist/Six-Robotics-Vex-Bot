//
// Created by Aryan Gajelli on 2020-02-24.
//
#pragma once
#ifndef _INERTIAL_HPP_
#define _INERTIAL_HPP_
#include "main.h"
#include "globals.h"
namespace Inertial {
	extern pros::Imu inertial;


	extern IterativePosPIDController controller;
	void initialize();

	void turnAngle(QAngle angle);
	void turnToAngle(QAngle angle);
	void turnToPoint(Point point);
}
#endif //_INERTIAL_HPP_
