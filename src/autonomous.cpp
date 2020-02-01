#include "main.h"
#include "globals.h"

using namespace mechanisms;

void auton_1()
{
    Timer timer;
    RQuantity start_timer = timer.millis();
    while(timer.millis() - start_timer <= 350_ms)
        lift::move_raw(-100);
    lift::move_raw(0);

    // Move tray up for intaking
    tray::control.setTarget(1800);
    tray::control.reset();
    while(!tray::control.isSettled())
        tray::move_raw(-tray::control.step(tray::get_pos_raw()) * (int)transT.getGearing());
    tray::move_raw(0);

    // Drive towards cubes at a slower speed and intake
    intakeMotors.moveVelocity(200);
    chassisController->setMaxVelocity(125);
    chassisController->moveDistance(3_ft + 4_in);
    intakeMotors.moveVelocity(0);

    // Turn a bit to move to the right of stacking position
    chassisController->setMaxVelocity(100);
    chassisController->moveDistance(-2_ft);

    chassisController->setMaxVelocity(150);
    // Drive & turn to stacking position
    chassisController->turnToPoint({8_in, 0_in});
    chassisController->moveDistance(15_in);
    chassisController->waitUntilSettled();

    // Drive forward into wall for alignment
    meccanumDrive->setBrakeMode(AbstractMotor::brakeMode::hold);
    start_timer = timer.millis();
    while(timer.millis() - start_timer <= 250_ms) meccanumDrive->forward(50);

    chassisController->turnAngle(-5_deg);

    // Move back from wall
    chassisController->setMaxVelocity(100);
    chassisController->moveDistance(-5_in);
    chassisController->waitUntilSettled();

    // Move back in to stack
    chassisController->moveDistanceAsync(2_in);

    start_timer = timer.millis();
    // Stack
    while(tray::get_pos_raw() > 100 && timer.millis() - start_timer <= 2500_ms)
        tray::move_raw(30);
    tray::move_raw(0);

    // Move away from stack
    chassisController->setMaxVelocity(100);
    chassisController->moveDistance(-1_ft);
    chassisController->waitUntilSettled();
}

void flipout()
{
    Timer timer;

    // Run intakes intake
    RQuantity start_timer = timer.millis();
    while(timer.millis() - start_timer <= 250_ms) {
        intakeMotors.moveVelocity(100);
    }

    // Move tray up and outtake
    start_timer = timer.millis();
    while(timer.millis() - start_timer <= 1000_ms) {
        tray::move_raw(100);
        intakeMotors.moveVelocity(-100);
    }

    // Move tray down and intake
    while(tray::get_pos_raw() < tray::DOWN_POS) {
        tray::move_raw(-50);
        intakeMotors.moveVelocity(100);
    }

    tray::move_raw(0);
    intakeMotors.moveVelocity(0);
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
    auton_1();

    /*chassisController->driveToPoint({0_in, 12_in});
	chassisController->waitUntilSettled();
	chassisController->driveToPoint({12_in, 12_in});
	chassisController->waitUntilSettled();
	chassisController->driveToPoint({12_in, 0_in});
	chassisController->waitUntilSettled();
	chassisController->driveToPoint({0_in, 0_in});*/

//    chassisController->turnAngle(90_deg);
//    chassisController->moveDistance(12_in);
//    chassisController->turnAngle(-90_deg);
//    chassisController->moveDistance(12_in);
//    chassisController->turnAngle(-90_deg);
//    chassisController->moveDistance(12_in);
//    chassisController->turnAngle(-90_deg);
//    chassisController->moveDistance(12_in);

//    printf("%f %f %f\n", leftEncoder.get(), rightEncoder.get(), centerEncoder.get());
}