#ifndef VEXROBOT_MECHANISMS_H
#define VEXROBOT_MECHANISMS_H
class Mechanisms
{
public:
  void tilter(int tilt);
  void lifter(int lift);
  void intake(int intakeSpeed);
  void update();
  void initialize();
};

#endif
