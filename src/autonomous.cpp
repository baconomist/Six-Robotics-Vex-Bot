#include "main.h"
#include "globals.h"
#include "autonomous.h"

using namespace mechanisms;

enum AutonSide {
    SIDE_RED = 1, SIDE_BLUE = -1
};
#define DEFAULT_MAX_VEL 150
/**
 * Wrapper function that has an option to set max velocity
 * */
void move_distance(QLength itarget, float max_vel = DEFAULT_MAX_VEL){
	chassisController->setMaxVelocity(max_vel);
	chassisController->moveDistance(itarget);
}
/**
 * Wrapper function that has an option to set max velocity
 * */
void turnAngle(QAngle idegTarget, float max_vel = DEFAULT_MAX_VEL){
	chassisController->setMaxVelocity(max_vel);
	chassisController->turnAngle(idegTarget);
}
/**
 * Moves lift down so it locks at the bottom
 */
void prep_tray_lift()
{
    Timer timer;

    // Lock lift down
    RQuantity start_timer = timer.millis();
    while (timer.millis() - start_timer <= 350_ms)
        lift::move_raw(-100);
    lift::move_raw(0);

    // Move tray up for intaking
    /*tray::control.setTarget(1800);
    tray::control.reset();
    while (!tray::control.isSettled())
        tray::move_raw(-tray::control.step(tray::get_pos_raw()) * (int) transT.getGearing());
    tray::move_raw(0);
*/
     }

void auton_1(AutonSide side) {
    prep_tray_lift();

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

void auton_2_big(AutonSide side)
{
    prep_tray_lift();

    Timer timer;
    RQuantity start_timer = timer.millis();

    // Drive towards cubes at a slower speed and intake
    intakeMotors.moveVelocity(200);
    chassisController->setMaxVelocity(100);
    chassisController->moveDistance(4_ft);

    chassisController->setMaxVelocity(150);
    // Drive & turn to stacking position
    if(side == SIDE_RED)
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

void auton_3_no_stack()
{
    Timer timer;
    RQuantity start_timer = timer.millis();

    // Drive towards cubes at a slower speed and intake
    intakeMotors.moveVelocity(200);
    chassisController->setMaxVelocity(100);
    chassisController->moveDistance(3_ft);
    intakeMotors.moveVelocity(0);

    chassisController->setMaxVelocity(150);
    chassisController->turnAngle(45_deg);
    chassisController->moveDistance(-3.25_ft);
    chassisController->turnAngle(-37_deg);

    chassisController->setMaxVelocity(100);
    intakeMotors.moveVelocity(200);
    chassisController->moveDistance(3_ft);
    intakeMotors.moveVelocity(0);

    chassisController->moveDistance(-1_ft);

    chassisController->waitUntilSettled();
}

void flipout() {
    Timer timer;

    // Run intakes intake
    RQuantity start_timer = timer.millis();
    while (timer.millis() - start_timer <= 250_ms) {
        intakeMotors.moveVelocity(100);
    }

    // Move tray up and outtake
    start_timer = timer.millis();
    while (tray::get_pos_raw()>1650 && timer.millis() - start_timer <= 1000_ms) {
        tray::move_raw(100);
        intakeMotors.moveVelocity(-100);
    }

    // Outtake more
    start_timer = timer.millis();
    while (timer.millis() - start_timer <= 100_ms) {
        intakeMotors.moveVelocity(-100);
    }

    // Move tray down and intake
    while (tray::get_pos_raw() < tray::DOWN_POS) {
        tray::move_raw(-50);
        intakeMotors.moveVelocity(-100);
    }

    tray::move_raw(0);
    intakeMotors.moveVelocity(0);
}

/**
 * Runs the square test to check if pid is working correctly
 * */
void square_test(){
	move_distance(1_ft);
	turnAngle(90_deg);
	move_distance(1_ft);
	turnAngle(90_deg);
	move_distance(1_ft);
	turnAngle(90_deg);
	move_distance(1_ft);
	turnAngle(90_deg);
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
    flipout();
    auton_3_no_stack();

}