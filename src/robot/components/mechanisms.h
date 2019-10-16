#ifndef VEXROBOT_MECHANISMS_H
#define VEXROBOT_MECHANISMS_H
class Mechanisms
{
public:
  void tilter(int speed);
  void lifter(int speed);
  void intake(int speed);
  void update();
  void initialize();
};

#endif
