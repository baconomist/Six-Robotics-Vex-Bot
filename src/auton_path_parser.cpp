//
// Created by Lucas on 9/20/2019.
//

#include "auton_path_parser.h"

nlohmann::json data;
AutonPathParser::AutonPathParser (std::string file_path) {
  std::ifstream readfile(file_path);
  readfile >> data;
  parseFile();
}

void AutonPathParser::parseFile () {

}

void AutonPathParser::dataToInstructions(std::vector<Vector2> points) {
  std::vector<double> lengths;
  std::vector<double> turns;

  for(int i = 0; i < points.size(); i++) {
    lengths.push_back(getDistance(points[i], points[i + 1]));
    turns.push_back(getAngle(points[i], points[i + 1 ], points[i + 2]));
  }
}

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
