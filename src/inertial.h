//
// Created by Aryan Gajelli on 2020-02-24.
//
#pragma once
#ifndef _INERTIAL_HPP_
#define _INERTIAL_HPP_

#include "main.h"
#include "globals.h"

namespace inertial {

    extern pros::Imu imu;
    extern TimeUtil settledStates;
    extern IterativePosPIDController controller;

    void initialize();

    void turnBy(QAngle signed_angle);

    void turnTo(QAngle abs_angle, int turn_dir);

    void turnTo(QAngle signed_angle);

    void turnTo(Point point);

    void arcTo(QAngle angle, float vx, float vy);
}
#endif //_INERTIAL_HPP_
