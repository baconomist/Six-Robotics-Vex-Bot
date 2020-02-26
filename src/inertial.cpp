//
// Created by Aryan Gajelli on 2020-02-24.
//

#include "inertial.h"
#include "hardware.h"

namespace inertial {
    pros::Imu imu(hardware::ports::INERTIAL_SENSOR);
    // Accurate to 0.05 of a degree
    TimeUtil settledStates = TimeUtilFactory::withSettledUtilParams(0.05f);
    IterativePosPIDController controller(0.01, 0.001, 0.001, 0,
                                         settledStates); // #TODO the gains need to be changed
    void initialize() {
        imu.reset();
        // Wait for inertial sensor to calibrate
        while (inertial::imu.is_calibrating());
    }

    void turnBy(QAngle angle) {
        double currAngle = imu.get_heading();
        // To convert to a QAngle use radians->QAngle
        turnTo(((QAngle) currAngle * degreeToRadian) + angle);
    }

    void turnTo(QAngle angle) {
        controller.setTarget(angle.convert(degree));
        controller.reset();
        while (!controller.isSettled()) {
            meccanumDrive->rotate(controller.step(imu.get_heading()));
        }
        meccanumDrive->stop();

        OdomState newOdomState = chassisController->getState();
        newOdomState.theta = (QAngle) imu.get_heading();
        chassisController->setState(newOdomState);
    }

    void turnTo(Point point) {
        QAngle targetAngle = OdomMath::computeAngleToPoint(point, chassisController->getState());
        turnTo(targetAngle);
    }
}