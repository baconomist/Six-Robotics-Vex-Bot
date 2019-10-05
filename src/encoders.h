#include "main.h"

#ifndef VEXBOT_ENCODERS_H
#define VEXBOT_ENCODERS_H
extern pros::ADIEncoder LeftXEncoder;
extern pros::ADIEncoder RightXEncoder;
extern pros::ADIEncoder YEncoder;
#endif
ADIEncoder LeftXEncoder(LEFT_X_ENCODER_TOP, LEFT_X_ENCODER_BOTTOM);
ADIEncoder RightXEncoder(RIGHT_X_ENCODER_TOP, RIGHT_X_ENCODER_BOTTOM);
ADIEncoder YEncoder(Y_ENCODER_TOP, Y_ENCODER_BOTTOM);
