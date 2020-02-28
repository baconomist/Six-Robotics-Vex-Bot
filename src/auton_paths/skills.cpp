#include "main.h"
#include "../globals.h"
#include "../autonomous.h"
#include "auton_paths.h"

using namespace mechanisms;
using namespace odometry;
using namespace inertial;

namespace auton_paths {

    Timer timer;
    RQuantity start_timer = timer.millis();

    void skillsAuton() {
        // Drive forward and intake 4-5 starting cubes
        intakeMotors.moveVelocity(200);
        chassisController->moveDistance(4_ft);
        chassisController->waitUntilSettled();


        // Drive back to the 3-cube line and turn to face them
        intakeMotors.moveVelocity(20);
        chassisController->driveToPoint({-2_ft, 0.9_ft}, true);
        chassisController->waitUntilSettled();
        chassisController->turnToPoint({-2_ft, 8_ft});
        chassisController->waitUntilSettled();


        //Drive and intake 3 cubes
        intakeMotors.moveVelocity(200);
        chassisController->driveToPoint({-2_ft, 3_ft + 9_in});
        chassisController->waitUntilSettled();

        intakeMotors.moveVelocity(20);
        chassisController->moveDistance(-1_ft);
        chassisController->waitUntilSettled();
        //turn to stacking area (unprotected zone)
        intakeMotors.moveVelocity(20);
        chassisController->setMaxVelocity(130);
        chassisController->turnToAngle(135_deg);

        chassisController->waitUntilSettled();


        //drive to stacking area (unprotected zone)
        chassisController->moveDistance(3_ft + 9_in);
        start_timer = timer.millis();
        while (timer.millis() - start_timer <= 500_ms) {
            meccanumDrive->forward(0.2);
        }
        chassisController->moveDistance(-2_in);


        start_timer = timer.millis();
        while (timer.millis() - start_timer <= 4000_ms && tray::get_pos_raw() > tray::UP_POS + 20) {
            tray::move_controlled(1, true);
            intakeMotors.moveVelocity(-50);
        }
        intakeMotors.moveVelocity(0);
        pros::delay(100);

        start_timer = timer.millis();
        while (timer.millis() - start_timer <= 200_ms) {
            meccanumDrive->forward(0.5);
        }
        pros::delay(100);
        chassisController->setMaxVelocity(50);
        chassisController->moveDistanceAsync(-1_ft);
        start_timer = timer.millis();
        while (timer.millis() - start_timer <= 1000_ms && tray::get_pos_raw() < 1550) {
            intakeMotors.moveVelocity(-30);
            tray::move_raw(-50);
        }
        hold_transmission_motors();
        chassisController->waitUntilSettled();
        chassisController->setMaxVelocity(DEFAULT_MAX_VEL);

        chassisController->turnToPoint({-4_ft, 1.5_ft});
        chassisController->waitUntilSettled();

        start_timer = timer.millis();
        while (timer.millis() - start_timer <= 500_ms) {
            meccanumDrive->forward(-10);
        }
        pros::delay(200);
        intakeMotors.moveVelocity(200);
        chassisController->moveDistance(3_ft + 5_in);
        chassisController->waitUntilSettled();
        intakeMotors.moveVelocity(0);

        chassisController->moveDistanceAsync(-4_in);
        start_timer = timer.millis();
        while (timer.millis() - start_timer <= 200_ms) {
            intakeMotors.moveVelocity(-60);
        }
        chassisController->waitUntilSettled();
    }
}