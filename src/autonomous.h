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
void drop_tray();
void drop_lift();
void move_lift_to(int pos);
void tower_with_cube_in_tray(int height);

#endif //VEXROBOT_AUTONOMOUS_H
