#include "main.h"

// Torque
#define MOTOR_GEARSET_RED pros::E_MOTOR_GEARSET_36

// Standard
#define MOTOR_GEARSET_GREEN pros::E_MOTOR_GEARSET_18

// Speed
#define MOTOR_GEARSET_BLUE pros::E_MOTOR_GEARSET_06

#define MOTOR_GEARSET_RED_RPM 100;
#define MOTOR_GEARSET_GREEN_RPM 200;
#define MOTOR_GEARSET_BLUE_RPM 600;

int get_gearset_rpm(pros::motor_gearset_e gearset);
