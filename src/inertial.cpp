//
// Created by Aryan Gajelli on 2020-02-24.
//

#include "globals.h"

using namespace odometry;
namespace inertial {
    pros::Imu imu(hardware::ports::INERTIAL_SENSOR);
    // Accurate to 0.05 of a degree
    TimeUtil settledStates = TimeUtilFactory::withSettledUtilParams(0.5, 5, 300_ms);
    IterativePosPIDController controller(0.02, 0.0001, 0.0005, 0, settledStates); // #TODO the gains need to be changed

    double zero_precision = 0.5;

    double get_heading() {
        if (imu.get_heading() > 360 - zero_precision || imu.get_heading() < zero_precision)
            return 0;
        return imu.get_heading();
    }

    void initialize() {
        imu.reset();
        // Wait for inertial sensor to calibrate
        while (inertial::imu.is_calibrating());
    }

    void turnBy(QAngle angle) {
        double currAngle = get_heading();
        // To convert to a QAngle use radians->QAngle
        turnTo((QAngle) (fmod(currAngle + angle.convert(degree), 360) * degreeToRadian));
    }

    void turnTo(QAngle signed_angle) {
        if (signed_angle < 0_deg) {
            signed_angle += 360_deg;
            turnTo(signed_angle, -1);
            return;
        }
        turnTo(signed_angle, 1);
    }

    void turnTo(QAngle angle, int turn_dir) {
        double targetAngle = angle.convert(degree);
        controller.setTarget(targetAngle);
        controller.reset();
        int direction = 1;

        while (!controller.isSettled()) {
            // Prevent indefinite turning
            if (targetAngle > get_heading())
                direction = 1;
            else
                direction = -1;


            if(turn_dir == -1 && get_heading() <= targetAngle && abs(get_heading() - targetAngle) <= 5) {
                break;
            }

            meccanumDrive->rotate(controller.step(get_heading()) * direction * turn_dir);
        }
        meccanumDrive->stop();
    }

    void turnTo(Point point) {
        QAngle targetAngle = OdomMath::computeAngleToPoint(point, chassisController->getState());
        turnTo(targetAngle);
    }

    void arcTo(QAngle angle, float vx, float vy) {
        while (abs(imu.get_heading() - angle.convert(degree)) > 2.0f) {
            meccanumDrive->driveVector(vx, vy);
        }
        meccanumDrive->stop();
    }

}