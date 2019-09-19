#include "main.h"
#include "misc.h"

#ifndef VEXBOT_ENCODERS_H
#define VEXBOT_ENCODERS_H
#define LeftXEncoder pros::ADIEncoder(LEFT_X_ENCODER_TOP, LEFT_X_ENCODER_BOTTOM)
#define RightXEncoder pros::ADIEncoder(RIGHT_X_ENCODER_TOP, RIGHT_X_ENCODER_BOTTOM)
#define YEncoder pros::ADIEncoder(Y_ENCODER_TOP, Y_ENCODER_BOTTOM)
#endif
