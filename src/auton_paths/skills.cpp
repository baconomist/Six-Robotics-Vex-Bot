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
        intakeMotors.moveVelocity(200);
        moveDistance(3_ft + 9_in, {0.72, 1.5, 10});
        pros::delay(100);
        turnTo(-28_deg);
        intakeMotors.moveVelocity(0);
        moveDistance(-4_ft);
        turnTo(359.5_deg);

        intakeMotors.moveVelocity(200);
//        moveDistance(2.9_ft, {0.72, 1.5, 10});
        // Intake 1 less cube
        moveDistance(2.9_ft - 6_in, {0.72, 1.5, 10});

        // Move in to stack
        turnTo(150_deg);
//        moveDistance(2.9_ft, {0.61, 1.5, 10});
        moveDistance(2.9_ft - 6_in, {0.61, 1.5, 10});
        intakeMotors.moveVelocity(0);

        stack();

        drop_tray();

        // Move in a little bit, helps with wall alignment
        moveDistance(3_in);
        intakeMotors.moveVelocity(200);
        turnTo(273_deg);

        // Drive back into wall for alignment
        meccanumDrive->forward(-0.25f);
        pros::delay(1200);
        meccanumDrive->forward(0.1f);
        pros::delay(200);
        meccanumDrive->forward(-1.0f);
        pros::delay(500);


        // Drive to tower 1
        moveDistance(0.8_ft, {0.2, 0.5, 10});
        moveDistance(3_ft, {0.5, 1.5, 10});
        pros::delay(500);

        moveDistance(-7_in);
        tower_with_cube_in_tray(2460);

        // Drive to tower 2
        intakeMotors.moveVelocity(0);
        moveDistance(-15_in - 5_in);
        drop_lift();
        turnTo(359.5_deg);

        intakeMotors.moveVelocity(200);
        moveDistance(2.4_ft,{0.5, 1.5, 10});
        pros::delay(500);

        moveDistance(-7_in);
        tower_with_cube_in_tray(2900);
    }
}