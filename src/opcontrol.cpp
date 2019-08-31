#include "main.h"
//#include "okapi/api.hpp"

//using namespace okapi;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enablpred via
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

pros::Motor trayLeft(4, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor trayRight(5, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor frontLeftDrive(1, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor frontRightDrive(2, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backLeftDrive(9, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backRightDrive(10, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES);

int min(int a, int b){
	return a>b? b: a;


void opcontrol() {
    bool setting_up = true;
	pros::Controller master(pros::E_CONTROLLER_MASTER);
    trayLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    trayRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	while (true) {
        if ((trayLeft.get_position() >= 595) && (trayLeft.get_position() <= 605) && setting_up) {
    		trayLeft.move_absolute(0, 200);
    		trayRight.move_absolute(0, 200);
            setting_up = false;
    	}

		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

        trayLeft.move_velocity(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
        trayRight.move_velocity(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));


        // Mechanum drive
        int turn = master.get_analog(ANALOG_RIGHT_X);
	int velLX = min(127,master.get_analog(ANALOG_LEFT_X))*200/127;//^^
        int forward = master.get_analog(ANALOG_RIGHT_Y);
        int sideways = 0;
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            sideways = -127;
            // Controller analog ranges from -127 to 127
		driveLF.move_velocity(velLY+velRX);
		driveLB.move_velocity(velLY-velRX);
		driveRF.move_velocity(velLY-velRX);
		driveRB.move_velocity(velLY+velRX);
	}else if(abs(velLY)<deadZone && abs(velLX)>deadZone){
		//turns on point if the X dir is greater than dead zone and Y dir is within dead zone
		driveLF.move_velocity(velLX+velRX);
		driveLB.move_velocity(velLX-velRX);
		driveRF.move_velocity(-velLX-velRX);
		driveRB.move_velocity(-velLX+velRX);
  }else{
		//arcade control + strafe
		driveLF.move_velocity(velLY-velLX+velRX);
		driveLB.move_velocity(velLY-velLX-velRX);
		driveRB.move_velocity(velLY+velLX+velRX);
		driveRF.move_velocity(velLY+velLX-velRX);
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            sideways = 127;
        }

void transmission(){
	/*
	uses 2 motors to control lift + tray
	tray = transB(hold) and transT(+- power)
        int frontLeft = turn + forward + sideways;
        int backLeft = turn + forward - sideways;
        int frontRight = forward - turn - sideways;
        int backRight = turn - forward + sideways;

	int tilt = 50*(master.get_digital(DIGITAL_R1)-master.get_digital(DIGITAL_R2));//sets tilit speed to 50 * the direction, scaled to match internal gearset
	int lift = 100*(master.get_digital(DIGITAL_L1)-master.get_digital(DIGITAL_L2));//sets lift speed to 100 * the direction, scaled to match internal gearset
	if(tilt){
		//moves the tray forwards and backwards
		transB.move_velocity(0);//uses motor brake(hold) to prevent motor from turning
        frontLeftDrive.move_velocity(frontLeft * 100);
	} else if(lift){
		//moves lift
        backLeftDrive.move_velocity(backLeft * 100);
        frontRightDrive.move_velocity(frontRight * 100);
	}
	else{
		//holds the motors in the current postion
        backRightDrive.move_velocity(backRight * 100);
		transT.move_velocity(0);

}
void opcontrol() {
	while(true){
		arcade();
		transmission();
		pros::delay(20);
	}
}
