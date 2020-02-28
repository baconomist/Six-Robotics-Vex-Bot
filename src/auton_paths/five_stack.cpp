#include "main.h"
#include "../globals.h"
#include "../autonomous.h"
#include "auton_paths.h"

using namespace mechanisms;
using namespace odometry;
using namespace inertial;

namespace auton_paths {

    void redAutonFiveStack() {
        intakeMotors.moveVelocity(200);
        moveDistance(3_ft + 9_in, {0.68, 1.5, 10});
        turnTo(157_deg);
        moveDistance(3_ft);
        intakeMotors.moveVelocity(0);

        // Stack
        stack();
    }

    void blueAutonFiveStack() {
        intakeMotors.moveVelocity(200);
        moveDistance(3_ft + 9_in, {0.68, 1.5, 10});
        turnTo(-155_deg);
        moveDistance(3_ft);
        intakeMotors.moveVelocity(0);

        // Stack
        stack();
    }

}