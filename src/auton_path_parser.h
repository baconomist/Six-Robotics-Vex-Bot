//
// Created by Lucas on 9/20/2019.
//

#ifndef VEXROBOT_AUTON_PATH_PARSER_H
#define VEXROBOT_AUTON_PATH_PARSER_H

#include "main.h"
#include "utils/vector2.h" //points for angle calculation
#include "json.h"
#include <vector>
#include <stdio.h>
#include <fstream>
#include <math.h> //atan2, pi

class AutonPathNode
{

};

class AutonPathParser
{
public:
  AutonPathParser(char* file_path);

private:
  void parseFile();
  // NOTE: std::vector not to be confused with Vector2.
  // std::vector is basically an array, Vector2 is a point.
  void dataToInstructions(std::vector<Vector2> points);
  double getAngle(Vector2, Vector2, Vector2);
  double getDistance(Vector2, Vector2);
};

#endif //VEXROBOT_AUTON_PATH_PARSER_H
