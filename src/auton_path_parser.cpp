//
// Created by Lucas on 9/20/2019.
//

#include "main.h"
#include "auton_path_parser.h"
#include <stdio.h>
#include "stdlib.h"

// nlohmann::json data;
AutonPathParser::AutonPathParser (char* file_path) {
  std::string STRING;
  std::ifstream infile;
  infile.open("/usd/path.json");
  while(!infile.eof())
  {
    getline(infile, STRING);
    std::cout << STRING;
  }
  infile.close();

  /*FILE * readfile;
  readfile = fopen("/usd/path.json", "r");
  fseek(readfile, 0, SEEK_END);
  int filesize = ftell(readfile);
  char buf[filesize];
  fread(buf, filesize, 1, readfile);

  // std::cout << filesize << "\n";
  // printf("%s", buf);

  char c = fgetc(readfile);
  while (c != EOF)
  {
      printf("%u\n", c);
      c = fgetc(readfile);
  }

  fclose(readfile);*/


  // data = nlohmann::json::parse(readfile);
  // parseFile();
}

/**
* Turns JSON data into a vector of points
*/
void AutonPathParser::parseFile () {
  // std::cout << data[0];
}

/**
* Turns vector of points into bot drive instructions
*/
void AutonPathParser::dataToInstructions(std::vector<Vector2> points) {
  std::vector<double> lengths;
  std::vector<double> turns;

  for(int i = 0; i < points.size(); i++) {
    lengths.push_back(getDistance(points[i], points[i + 1]));
    turns.push_back(getAngle(points[i], points[i + 1 ], points[i + 2]));
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
