//
// Created by Aryan Gajelli on 2020-02-27.
//
#pragma once
#ifndef _ODOMETERY_HPP_
#define _ODOMETERY_HPP_

#include "main.h"

namespace odometry {

    const PathfinderLimits defaultPathFinderLimits = {1, 2.5, 10.0};

    extern std::shared_ptr<XDriveModel> meccanumDrive;
    extern std::shared_ptr<okapi::OdomChassisController> chassisController;
    extern std::shared_ptr<AsyncMotionProfileController> profileController;

    void initialize();

    void moveDistance(QLength distance, PathfinderLimits limits = defaultPathFinderLimits);
}
#endif //_ODOMETERY_HPP_
