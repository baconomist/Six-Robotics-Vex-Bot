//
// Created by Lucas on 9/20/2019.
//

#ifndef VEXROBOT_AUTON_PATH_PARSER_H
#define VEXROBOT_AUTON_PATH_PARSER_H

#include "main.h"
#include "../utils/vector2.h" //points for angle calculation
#include "json.h"
#include <vector>
#include <stdio.h>
#include <fstream>
#include <math.h> //atan2, pi

class AutonPathParser
{
public:
    AutonPathParser(std::string file_path);

    std::vector<double> lengths;
    std::vector<double> turns;

private:
    void parseFile(nlohmann::json pathJSON);

    void dataToInstructions(std::vector<Vector2> points);

    double getAngle(Vector2, Vector2, Vector2);

    double getDistance(Vector2, Vector2);
};

#endif //VEXROBOT_AUTON_PATH_PARSER_H
