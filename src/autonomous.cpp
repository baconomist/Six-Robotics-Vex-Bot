
#include "main.h"
#include "motor_gearsets.h"
#include "kalman_filter.h"

#include "robot/motors.h"


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

using namespace pros::c;
float get_measurement(){
    return motor_get_position(1);
}

void autonomous(){
    motor_set_gearing(1, MOTOR_GEARSET_BLUE);

    motor_set_encoder_units(1, E_MOTOR_ENCODER_DEGREES);

    /*while(1)
     {
         motor_move_absolute (1, 360, 127);
         motor_set_zero_position(1, 0);
         delay(1000);
     }*/


    double speed = 20;

    double start = millis();

    char buffer[50];

    pros::Controller master(pros::E_CONTROLLER_MASTER);

    std::cout << kalmanFilter(get_measurement(), 1, &get_measurement, 1, 2);

    while (1) {
        motor_move(1, speed);

        if (millis() - start >= 100) {
            start = millis();
            speed++;

            //pros::lcd::clear();
            //pros::lcd::set_text(0, "HIHIHIIHIIH");
             //pros::lcd::set_text(7, buffer);


            sprintf(buffer, "%f", motor_get_temperature(1));
            master.set_text(2, 2, buffer);

        }

        printf("%f \n", motor_get_temperature(1));
    }
}
