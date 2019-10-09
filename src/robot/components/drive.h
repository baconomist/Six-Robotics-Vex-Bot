//
// Created by Lucas on 9/27/2019.
//

#ifndef VEXROBOT_DRIVE_H
#define VEXROBOT_DRIVE_H

enum DriveMode
{
    TANK,
    ARCADE
};


class Drive
{
public:
    DriveMode driveMode = TANK;

    void tank();

    void arcade();

    void transmission();

    void update();
};


#endif //VEXROBOT_DRIVE_H
