#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "auton_paths/auton_paths.h"

using namespace mechanisms;
using namespace odometry;
using namespace inertial;
using namespace auton_paths;

Timer timer;
RQuantity start_timer = timer.millis();

void stack() {
    start_timer = timer.millis();
    while (timer.millis() - start_timer <= 4000_ms && tray::get_pos_raw() > tray::UP_POS + 20) {
        tray::move_controlled(1, true);
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


void testing() {

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
