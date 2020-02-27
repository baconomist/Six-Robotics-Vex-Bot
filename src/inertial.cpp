//
// Created by Aryan Gajelli on 2020-02-24.
//

#include "globals.h"
using namespace odometry;
namespace inertial {
	pros::Imu imu(hardware::ports::INERTIAL_SENSOR);
	// Accurate to 0.05 of a degree
	TimeUtil settledStates = TimeUtilFactory::withSettledUtilParams(0.05);
	IterativePosPIDController controller(0.01, 0.001, 0.001, 0, settledStates); // #TODO the gains need to be changed

	double zero_precision = 0.5;
	double get_heading(){
		if(imu.get_heading()>360-zero_precision || imu.get_heading()<zero_precision)
			return 0;
		return imu.get_heading();
	}

	void initialize() {
		imu.reset();
		// Wait for inertial sensor to calibrate
		while (inertial::imu.is_calibrating());
	}

	void turnBy(QAngle angle) {

		double currAngle = imu.get_heading();
		// To convert to a QAngle use radians->QAngle
		turnTo(((QAngle)currAngle * degreeToRadian) + angle);
	}

	void turnTo(QAngle angle) {

		double targetAngle = angle.convert(degree);

		int dir = (targetAngle>0)-(targetAngle<0);
		OdomState newOdomState = chassisController->getState();
		controller.setTarget(targetAngle);
		controller.reset();
		while (!controller.isSettled()) {
			meccanumDrive->rotate(controller.step(imu.get_heading()));
		}
		meccanumDrive->stop();

		newOdomState.theta = (QAngle)imu.get_heading();
		chassisController->setState(newOdomState);
	}

	void turnTo(Point point) {
		QAngle targetAngle = OdomMath::computeAngleToPoint(point, chassisController->getState());
		turnTo(targetAngle);
	}

}