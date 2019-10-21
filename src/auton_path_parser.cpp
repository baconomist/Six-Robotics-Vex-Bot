//
// Created by Lucas on 9/20/2019.
//

#include "main.h"
#include "auton_path_parser.h"
#include <stdio.h>
#include "stdlib.h"

// nlohmann::json data;
AutonPathParser::AutonPathParser (std::string file_path) {
    std::ifstream pathFile;
    pathFile.open(file_path);
    std::string data((std::istreambuf_iterator<char>(pathFile)),
               std::istreambuf_iterator<char>());
    pathFile.close();
    parseFile(nlohmann::json::parse(data));
}

/**
* Turns JSON data into a vector of points
*/
void AutonPathParser::parseFile (nlohmann::json pathJSON) {
    std::vector<Vector2> points;
    for(int i = 0; i < pathJSON.size(); i++) {
          points.push_back(Vector2(pathJSON[i]["x_in"], pathJSON[i]["y_in"]));
      }
    dataToInstructions(points);
}

/**
* Turns vector of points into bot drive instructions
*
* Example usage:
* bot.move_distance(lengths[i]);
* bot.rotate_degrees(turns[i]);
*/
void AutonPathParser::dataToInstructions(std::vector<Vector2> points) {
  for(int i = 0; i < points.size(); i++) {
    lengths.push_back(getDistance(points[i], points[i + 1]));
    turns.push_back(getAngle(points[i], points[i + 1 ], points[i + 2]));
  }
  for(int i = 0; i < lengths.size(); i++) {
      printf("forward %f and turn %f", lengths[i], turns[i]);
  }
}

/**
* Gets the turn angle on the middle point of given points
*/
double getAngle(Vector2 p1, Vector2 p2, Vector2 p3) {
  Vector2 v1 = p1 - p2;
  Vector2 v2 = p3 - p2;
  double angle = -(180/M_PI)*atan2(v1.x*v2.y - v1.y*v2.x,
    v1.x*v2.x + v1.y*v2.y);
    return angle;
  }

  double getDistance(Vector2 p1, Vector2 p2) {
    double a = abs(p1.x - p2.x);
    double b = abs(p1.y - p2.y);
    double c = sqrt(a*a + b*b);
    return c;
  }
