#include "main.h"
#include "../globals.h"
#include "../autonomous.h"
#include "auton_paths.h"

using namespace mechanisms;
using namespace odometry;
using namespace inertial;

namespace auton_paths {

    void blue8Auton() {
        Timer timer;
        RQuantity start_timer = timer.millis();
        // Drive forward and intake 4-5 starting cubes
        chassisController->setMaxVelocity(140);
        intakeMotors.moveVelocity(200);
        chassisController->moveDistance(3_ft + 5_in);
        chassisController->waitUntilSettled();

        // Turn and drive to the next line of cubes
        intakeMotors.moveVelocity(20);
        chassisController->turnToAngle(-40_deg);
        chassisController->moveDistance(-3.5_ft);
        chassisController->waitUntilSettled();
        chassisController->turnToAngle(-0_deg);
        chassisController->waitUntilSettled();

        //Drive and intake 3 cubes
        intakeMotors.moveVelocity(200);
        chassisController->driveToPoint({2_ft, 3_ft});
        chassisController->waitUntilSettled();
    }

    void onePointAuton() {
        Timer timer;
        RQuantity start_timer = timer.millis();
        start_timer = timer.millis();

        while (timer.millis() - start_timer <= 2000_ms) {
            meccanumDrive->xArcade(0.7, 0, 0);
        }
        start_timer = timer.millis();
        while (timer.millis() - start_timer <= 1000_ms) {
            meccanumDrive->xArcade(-0.7, 0, 0);
        }
        meccanumDrive->stop();
    }

    void redAutonSevenStack() {
        intakeMotors.moveVelocity(200);
        moveDistance(2.3_ft, {0.72, 1.5, 10});
        pros::delay(100);
        turnTo(-49_deg);
        intakeMotors.moveVelocity(0);
        moveDistance(-2.7_ft);
        turnTo(359.5_deg);

        intakeMotors.moveVelocity(200);
        moveDistance(2.8_ft, {0.72, 1.5, 10});
        turnTo(157_deg);
        moveDistance(2.8_ft);
        intakeMotors.moveVelocity(0);

        // Stack
        stack();
    }
}