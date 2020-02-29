#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "auton_paths/auton_paths.h"

using namespace mechanisms;
using namespace odometry;
using namespace inertial;

#define DEFAULT_MAX_VEL 180

Timer timer;
RQuantity start_timer = timer.millis();

void stack() {
    start_timer = timer.millis();
    while (timer.millis() - start_timer <= 4000_ms && tray::get_pos_raw() > tray::UP_POS + 20) {
        tray::move_controlled_slow(1, true);
        intakeMotors.moveVelocity(-35);
    }
    intakeMotors.moveVelocity(0);
    intakeMotors.moveVelocity(-40);
    moveDistance(3_in);
    moveDistance(1_in);
    moveDistance(-10_in);
}

void drop_tray() {
    while (tray::get_pos_raw() < tray::DOWN_POS + 50)
        tray::move_raw(-40);
    tray::move_raw(0);
}

void drop_lift()
{
    while (lift::get_pos_raw() < lift::DOWN_POS - 50)
        lift::move_raw(-40);
    lift::move_raw(0);
}

void tower_with_cube_in_tray(int height)
{
    // Move cube into intake
    intakeMotors.moveVelocity(-100);
    pros::delay(650);
    intakeMotors.moveVelocity(0);

    // Put cube into tower
    move_lift_to(height);
    moveDistance(6_in);
    intakeMotors.moveVelocity(-100);
    pros::delay(1000);
}

void move_lift_to(int pos) {
    // Tray is too far down to move lift
    while (tray::get_pos_raw() > lift::min_tray_pos_to_move_lift) {
        //intakeMotors.moveVelocity((int) intakeMotors.getGearing());
        tray::move_raw((int) transT.getGearing());
    }

    lift::control.setTarget(pos);
    lift::control.reset();
    while (!lift::control.isSettled()) {
        lift::move_raw(-lift::control.step(lift::get_pos_raw()) * (int) transT.getGearing());
        intakeMotors.moveVelocity(0);
    }

    mechanisms::hold_transmission_motors();
    intakeMotors.moveVelocity(0);
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

void arc_turn(QLength radius, float tan_vel_inch_per_s, QAngle stop_theta) {
    QLength s = radius * stop_theta.convert(radian);
    float time_s = s.convert(inch) / tan_vel_inch_per_s;
    float w = stop_theta.convert(radian) / time_s;
    float v = radius.convert(inch) * w;

    char buff[99];
    sprintf(buff, "%f", time_s);
    master.setText(1, 1, buff);

    start_timer = timer.millis();
    while ((timer.millis() - start_timer).convert(second) <= time_s)
        meccanumDrive->driveVector(sqrt(v * v - (-0.2) * (-0.2)), -0.2);
    meccanumDrive->stop();
}

void testing() {
    meccanumDrive->setBrakeMode(AbstractMotor::brakeMode::brake);
    intakeMotors.moveVelocity(200);
    arcTo(360_deg - 45_deg, 0.75f, -0.4f);
    meccanumDrive->stop();
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
//    turnTo(90_deg);
//    turnTo(90_deg);
//    turnBy(90_deg);
//    turnBy(90_deg);
//    turnBy(90_deg);
//    turnBy(90_deg);
//    turnBy(90_deg);
//    turnBy(90_deg);
//    turnBy(90_deg);

//    testing();
//    move_lift_to(lift::UP_POS);
//    move_lift_to(lift::UP_POS);
//    turnTo(90_deg);
//    turnTo(-28_deg);
//    turnTo(-90_deg);
//    turnTo(359.5_deg);
    //turnTo(0_deg);

    auton_paths::skillsAuton();
}
