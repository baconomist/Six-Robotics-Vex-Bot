
#include "main.h"
#include "headers/motor_gearsets.h"
#include "headers/kalman_filter.h"
#include "headers/motors.h"
//#include "headers/controllers.h"

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

    pros::lcd::initialize();

    double speed = 20;

    double start = millis();

    char buffer[50];

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
            //master.set_text(2, 2, buffer);

        }

        printf("%f \n", motor_get_temperature(1));
    }
}
