//
// Created by Lucas on 11/8/2019.
//

#ifndef VEXROBOT_ARC_TURNER_H
#define VEXROBOT_ARC_TURNER_H

#include "../motion_control/PID.h"

extern float rot_target_radians;
extern float move_distance;
extern float turn_distance;
extern P *moveP;
extern P *turnP;


void update_mtp();

void initialize_mtp(float target_x, float target_y);

#endif //VEXROBOT_ARC_TURNER_H
