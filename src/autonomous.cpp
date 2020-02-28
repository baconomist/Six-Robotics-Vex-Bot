#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "auton_paths/auton_paths.h"

using namespace mechanisms;
using namespace odometry;
using namespace inertial;
enum AutonSide {
    SIDE_RED = 1, SIDE_BLUE = -1
};
#define DEFAULT_MAX_VEL 180

Timer timer;
RQuantity start_timer = timer.millis();
void stack(){
    start_timer = timer.millis();
    while (timer.millis() - start_timer <= 4000_ms && tray::get_pos_raw() > tray::UP_POS + 20) {
        tray::move_controlled(1,true);
        intakeMotors.moveVelocity(-35);

    }
    intakeMotors.moveVelocity(0);
    intakeMotors.moveVelocity(-40);
    moveDistance(3_in);
    moveDistance(-10_in);
}
/**
 * Runs the square test to check if pid is working correctly
 * */
void squareTest() {
    moveDistance(1_ft);
    turnTo(90_deg);
    moveDistance(1_ft);
    turnTo(90_deg);
    moveDistance(1_ft);
    turnTo(90_deg);
    moveDistance(1_ft);
    turnTo(90_deg);
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

    // Stack
    stack();
}

void redAutonFiveStack(){
    intakeMotors.moveVelocity(200);
    moveDistance(3_ft + 9_in, {0.68,1.5,10});
    turnTo(157_deg);
    moveDistance(3_ft);
    intakeMotors.moveVelocity(0);

    // Stack
    stack();
}

void redAutonSevenStack(){
    intakeMotors.moveVelocity(200);
    moveDistance(2.3_ft,{0.72,1.5,10});
    pros::delay(100);
    turnTo(-49_deg);
    intakeMotors.moveVelocity(0);
    moveDistance(-2.7_ft);
    turnTo(359.5_deg);

    intakeMotors.moveVelocity(200);
    moveDistance(2.8_ft, {0.72,1.5,10});
    turnTo(157_deg);
    moveDistance(2.8_ft);
    intakeMotors.moveVelocity(0);

    // Stack
    stack();


}


void blueAutonFiveStack(){
    intakeMotors.moveVelocity(200);
    moveDistance(3_ft + 9_in, {0.68,1.5,10});
    turnTo(-155_deg);
    moveDistance(3_ft);
    intakeMotors.moveVelocity(0);

    // Stack
    stack();
}
void testing(){
    meccanumDrive->driveVector(200,30);
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
    redAutonSevenStack();
}
