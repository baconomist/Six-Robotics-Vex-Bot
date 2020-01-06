//
// Created by Lucas on 9/20/2019.
//

#ifndef VEXROBOT_AUTON_PATH_PARSER_H
#define VEXROBOT_AUTON_PATH_PARSER_H

#include "main.h"
#include "rapidjson/document.h"
#include "../utils/vector2.h" //points for angle calculation
#include <vector>
#include <stdio.h>
#include <fstream>
#include <math.h> //atan2, pi

class AutonPathParser
{
public:
    rapidjson::Document jsonDocument;
    AutonPathParser(std::string data);
    static AutonPathParser* FromFile(std::string file_path);

    std::vector<double> lengths;
    std::vector<double> turns;

private:
    void parseFile();

    void dataToInstructions(std::vector<Vector2> points);

    static double getAngle(Vector2, Vector2, Vector2);

    static double getDistance(Vector2, Vector2);
};

#endif //VEXROBOT_AUTON_PATH_PARSER_H
