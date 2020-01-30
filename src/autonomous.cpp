#include "main.h"
#include "globals.h"

using namespace mechanisms;

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
	leftEncoder.reset();
	rightEncoder.reset();
	centerEncoder.reset();
	intakeMotors.moveVelocity((int)intakeMotors.getGearing());
	chassisController->moveDistance(4_ft);

//    chassisController->driveToPoint((Point){0_in, 2_ft});
//	chassisController->waitUntilSettled();
//	chassisController->driveToPoint((Point){12_in, 12_in});
//	chassisController->waitUntilSettled();
//	chassisController->driveToPoint((Point){12_in, 0_in});
//	chassisController->waitUntilSettled();
//	chassisController->driveToPoint((Point){0_in, 0_in});
//    chassisController->turnAngle(90_deg);
//    chassisController->turnAngle(-90_deg);

//    chassisController->turnAngle(90_deg);
//    chassisController->moveDistance(12_in);
//    chassisController->turnAngle(-90_deg);
//    chassisController->moveDistance(12_in);
//    chassisController->turnAngle(-90_deg);
//    chassisController->moveDistance(12_in);
//    chassisController->turnAngle(-90_deg);
//    chassisController->moveDistance(12_in);

    chassisController->waitUntilSettled();
	intakeMotors.moveVelocity(0);

//    printf("%f %f %f\n", leftEncoder.get(), rightEncoder.get(), centerEncoder.get());
}