//
// Created by Aryan Gajelli on 2020-02-27.
//
#pragma once
#ifndef _ODOMETERY_HPP_
#define _ODOMETERY_HPP_
#include "main.h"
namespace odometry{
	extern std::shared_ptr<XDriveModel> meccanumDrive;
	extern std::shared_ptr<okapi::OdomChassisController> chassisController;
	extern std::shared_ptr<AsyncMotionProfileController> profileController;
	void initialize();
}
#endif //_ODOMETERY_HPP_
