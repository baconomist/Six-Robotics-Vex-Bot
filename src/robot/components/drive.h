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
  DriveMode driveMode = ARCADE;

  void tank();

  void arcade();

  void update();

  void initialize();
};


#endif //VEXROBOT_DRIVE_H
