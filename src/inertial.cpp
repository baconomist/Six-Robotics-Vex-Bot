//
// Created by Aryan Gajelli on 2020-02-24.
//

#include "inertial.h"
#include "hardware.h"
namespace Inertial {
	pros::Imu inertial(hardware::ports::INERTIAL_SENSOR);
	TimeUtil settledStates = TimeUtilFactory().withSettledUtilParams();//#TODO change the settled params to be accurate to what we want
	IterativePosPIDController controller = IterativePosPIDController(0.001,0,0,0,settledStates); //#TODO the gains need to be changed
	void initialize(){
		inertial.reset();
	}


	void turnAngle(QAngle angle){
		double currAngle = inertial.get_heading();
		controller.setTarget(currAngle+angle.convert(degree));
		controller.reset();
		while(!controller.isSettled()){
			double heading = inertial.get_heading();
			double output = controller.step(heading);
			meccanumDrive->rotate(output);
		}
	}

	void turnToAngle(QAngle angle){
		double currAngle = inertial.get_heading();
		controller.setTarget(angle.convert(degree));
		controller.reset();
		while(!controller.isSettled()){
			double heading = inertial.get_heading();
			double output = controller.step(heading);
			meccanumDrive->rotate(output);
		}
	}

	void turnToPoint(Point point){
		QAngle targetAngle = OdomMath::computeAngleToPoint(point,chassisController->getState());
		turnToAngle(targetAngle);
	}
}