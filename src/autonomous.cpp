#include "main.h"
#include "globals.h"
#include "autonomous.h"

using namespace mechanisms;

enum AutonSide {
    SIDE_RED = 1, SIDE_BLUE = -1
};
#define DEFAULT_MAX_VEL 180

/**
 * Wrapper function that has an option to set max velocity
 * */
void moveDistance(QLength itarget, float max_vel = DEFAULT_MAX_VEL) {
    chassisController->setMaxVelocity(max_vel);
    chassisController->moveDistance(itarget);
}

/**
 * Wrapper function that has an option to set max velocity
 * */
void turnAngle(QAngle idegTarget, float max_vel = DEFAULT_MAX_VEL) {
    chassisController->setMaxVelocity(max_vel);
    chassisController->turnAngle(idegTarget);
}

/**
 * Moves lift down so it locks at the bottom
 */
void prepTrayLift() {
    Timer timer;

    // Lock lift down
    RQuantity start_timer = timer.millis();
    while (timer.millis() - start_timer <= 350_ms)
        lift::move_raw(-100);
    lift::move_raw(0);
}

/**
 * Four point auton for small goal
 *
 * @param side The AutonSide the bot is starting on
 */
void auton1(AutonSide side) {
    prepTrayLift();

    Timer timer;
    RQuantity start_timer = timer.millis();

    // Drive towards cubes at a slower speed and intake
    intakeMotors.moveVelocity(200);
    chassisController->setMaxVelocity(125);
    chassisController->moveDistance(3_ft + 4_in);
    intakeMotors.moveVelocity(0);

    // Move back for stacking position
    chassisController->setMaxVelocity(150);
    chassisController->moveDistance(-2_ft);

    chassisController->setMaxVelocity(150);
    // Drive & turn to stacking position
    chassisController->turnToPoint({18_in * side, 0_in});

    chassisController->moveDistance(15_in);
    chassisController->waitUntilSettled();

    start_timer = timer.millis();
    // Stack
    while (tray::get_pos_raw() > 150 && timer.millis() - start_timer <= 2500_ms)
        tray::move_raw(30);
    tray::move_raw(0);

    // Move away from stack
    chassisController->setMaxVelocity(125);
    chassisController->moveDistance(-1_ft);
    chassisController->waitUntilSettled();
}

/**
 * Six point auton (depending on how the stack falls) for large goal
 *
 * @param side The AutonSide the bot is starting on
 */
void auton2Big(AutonSide side) {
    prepTrayLift();

    Timer timer;
    RQuantity start_timer = timer.millis();

    // Drive towards cubes at a slower speed and intake
    intakeMotors.moveVelocity(200);
    chassisController->setMaxVelocity(100);
    chassisController->moveDistance(4_ft);

    chassisController->setMaxVelocity(150);
    // Drive & turn to stacking position
    if (side == SIDE_RED)
        chassisController->turnToPoint({-2_ft, 18_in});
    else
        chassisController->turnToPoint({8_in, 0_in});

    chassisController->moveDistance(15_in);
    chassisController->waitUntilSettled();

    chassisController->turnAngle(5_deg * side);

    intakeMotors.moveVelocity(0);

    start_timer = timer.millis();
    // Stack
    while (tray::get_pos_raw() > 100 && timer.millis() - start_timer <= 2500_ms)
        tray::move_raw(30);
    tray::move_raw(0);

    // Move away from stack
    chassisController->setMaxVelocity(100);
    chassisController->moveDistance(-1_ft);
    chassisController->waitUntilSettled();
}

/**
 * Collects 8 cubes and waits
 */
void auton3NoStack(AutonSide side) {
    Timer timer;
    RQuantity start_timer = timer.millis();

    // Drive towards cubes at a slower speed and intake
    intakeMotors.moveVelocity(200);
    chassisController->setMaxVelocity(100);
    chassisController->moveDistance(3_ft);
    intakeMotors.moveVelocity(0);

    // Turn and drive to next line of cubes
    chassisController->setMaxVelocity(150);
    chassisController->turnAngle(45_deg * side);
    chassisController->moveDistance(-3.25_ft);
    chassisController->turnAngle(-37_deg * side);

    // Collect the next line
    chassisController->setMaxVelocity(100);
    intakeMotors.moveVelocity(200);
    chassisController->moveDistance(3_ft);
    intakeMotors.moveVelocity(0);

    chassisController->moveDistance(-1_ft);

    chassisController->waitUntilSettled();
}

/**
 * Flips out the tray for the beginning
 */
void flipout() {
    chassisController->moveDistance(10_in);
    chassisController->moveDistance(-10_in);

    // Move tray up and outtake
    Timer timer;
    RQuantity start_timer = timer.millis();
    while (tray::get_pos_raw() > 500 && timer.millis() - start_timer <= 1000_ms) {

        tray::move_raw(100);
        intakeMotors.moveVelocity(100);
    }

    // Outtake more
    start_timer = timer.millis();
    while (timer.millis() - start_timer <= 150_ms) {
        intakeMotors.moveVelocity(-100);
    }

    // Move tray down and intake
    while (tray::get_pos_raw() < 1650) {
        tray::move_raw(-50);
        intakeMotors.moveVelocity(100);
    }

    tray::move_raw(0);
    intakeMotors.moveVelocity(0);
}


/**
 * Runs the square test to check if pid is working correctly
 * */
void squareTest() {
    moveDistance(1_ft);
    turnAngle(90_deg);
    moveDistance(1_ft);
    turnAngle(90_deg);
    moveDistance(1_ft);
    turnAngle(90_deg);
    moveDistance(1_ft);
    turnAngle(90_deg);
}


/**
 * Collects ~8 cubes with no stack
 */
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

/**
 * One point auton, moves to the right and back
 */
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

/**
 * Programming skills run
 */
void skills() {

    Timer timer;
    RQuantity start_timer = timer.millis();

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
    chassisController->moveDistance(3_ft+9_in);
    start_timer = timer.millis();
    while(timer.millis()-start_timer<=500_ms){
        meccanumDrive->forward(0.2);
    }
    chassisController->moveDistance(-2_in);


    start_timer = timer.millis();
    while (timer.millis() - start_timer <= 4000_ms && tray::get_pos_raw() > tray::UP_POS + 20) {
        tray::move_controlled(1,true);
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

/**
* Runs the user autonomous code. This function will be started in its own task
* with the default priority and stack size whenever the robot is enabled via
* the Field Management System or the VEX Competition Switch in the autonomous
* mode. Alternatively, this function may be called in initialize or opcontrol
* for non-competition testing purposes.
*
* If the robot is disabled or communications is lost, the autonomous task
* will be stopped. Re-enabling the robot will restart the task, not re-start it
* from where it left off.
*/
void autonomous() {
   // chassisController->turnAngle(90_deg);
   //square_test();
   //chassisController->moveDistance(2_ft);
    skills();
}
