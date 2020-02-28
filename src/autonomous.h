//
// Created by Lucas on 2/1/2020.
//

#ifndef VEXROBOT_AUTONOMOUS_H
#define VEXROBOT_AUTONOMOUS_H

enum AutonSide {
    SIDE_RED = 1, SIDE_BLUE = -1
};
#define DEFAULT_MAX_VEL 180

void flipout();
void stack();

#endif //VEXROBOT_AUTONOMOUS_H
