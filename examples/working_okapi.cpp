#include "main.h"
#include "okapi/api.hpp"
#include "../src/globals.h"
#include "../src/ports.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

using namespace okapi::literals;
using namespace okapi;

void opcontrol()
{
    okapi::ADIEncoder leftEncoder(LEFT_Y_ENCODER_TOP, LEFT_Y_ENCODER_BOTTOM);
    okapi::ADIEncoder rightEncoder(RIGHT_Y_ENCODER_BOTTOM, RIGHT_Y_ENCODER_TOP, false);
    okapi::ADIEncoder centerEncoder(X_ENCODER_BOTTOM, X_ENCODER_TOP, false);

    IterativePosPIDController::Gains distanceGains;
    distanceGains.kP = 0.0005;
    distanceGains.kI = 0;
    distanceGains.kD = 0.00000;

    IterativePosPIDController::Gains turnGains;
    turnGains.kP = 0.0005;
    turnGains.kI = 0;
    turnGains.kD = 0.00000;

    IterativePosPIDController::Gains angleGains;
    angleGains.kP = 0.0005;
    angleGains.kI = 0;
    angleGains.kD = 0.00000;


    auto chassisController = ChassisControllerBuilder()
            .withMotors(LEFT_FRONT, -RIGHT_FRONT, -RIGHT_BACK, LEFT_BACK)
            .withSensors(
                    leftEncoder,
                    rightEncoder,
                    centerEncoder
            )
            .withGains(distanceGains, turnGains, angleGains)
            .withDimensions(okapi::AbstractMotor::gearset::green, {{3.25_in, 16_in}, okapi::imev5GreenTPR})
            .withOdometry({{3.25_in, 16_in}, okapi::quadEncoderTPR}, StateMode::CARTESIAN)
            .buildOdometry();

    Point point;
    point.x = 0_ft;
    point.y = 1_ft;
    printf("aaaa");
    //chassisController->moveDistance(12_in);
    //chassisController->waitUntilSettled();
    //chassisController->moveDistance(-12_in);
    chassisController->driveToPoint(point);
    chassisController->waitUntilSettled();
    printf("Settled");
    //chassisController->turnAngle(okapi::degree * 90);
    //chassisController->moveDistance(-okapi::inch * 12);
}

