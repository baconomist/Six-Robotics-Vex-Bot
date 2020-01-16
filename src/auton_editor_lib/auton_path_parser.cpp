//
// Created by Lucas on 9/20/2019.
//

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

#include "main.h"
#include "auton_path_parser.h"
#include <stdio.h>
#include <sstream>
#include "stdlib.h"

AutonPathParser::AutonPathParser(std::string data)
{
    // https://miloyip.github.io/rapidjson/md_doc_tutorial.html
    rapidjson::ParseResult result = jsonDocument.Parse(data.c_str());
    if(!result)
        std::cout << "Error in json data!" << "\n";

    parseFile();
}

/**
* Turns JSON data into a vector of points
*/
void AutonPathParser::parseFile()
{
    std::vector<Vector2> points;

    for (rapidjson::Value::MemberIterator itr = jsonDocument["path"][0].MemberBegin();
         itr != jsonDocument.MemberEnd(); ++itr)
    {
        points.push_back(Vector2(itr->value["x_in"].GetFloat(), itr->value["y_in"].GetFloat()));
    }

    dataToInstructions(points);
}

/**
* Turns vector of points into bot drive instructions
*/
void AutonPathParser::dataToInstructions(std::vector<Vector2> points)
{
    for (int i = 0; i < points.size(); i++)
    {
        lengths.push_back(getDistance(points[i], points[i + 1]));
        turns.push_back(getAngle(points[i], points[i + 1], points[i + 2]));
    }
//    for (int i = 0; i < lengths.size(); i++)
//    {
//         printf("auton_path_parser:46 - forward %f and turn %f\n", lengths[i], turns[i]);
//    }
}

/**
* Returns the turn angle on the middle point of given points
*/
double AutonPathParser::getAngle(Vector2 p1, Vector2 p2, Vector2 p3)
{
    Vector2 v1 = p1 - p2;
    Vector2 v2 = p3 - p2;
    double angle = -(180 / M_PI) * atan2(v1.x * v2.y - v1.y * v2.x,
                                         v1.x * v2.x + v1.y * v2.y);
    return angle;
}

/**
* Returns the distance between two points
*/
double AutonPathParser::getDistance(Vector2 p1, Vector2 p2)
{
    double a = abs(p1.x - p2.x);
    double b = abs(p1.y - p2.y);
    double c = sqrt(a * a + b * b);
    return c;
}

AutonPathParser *AutonPathParser::FromFile(std::string file_path)
{
    /*std::ifstream file;

    file.open(file_path);
    std::string data((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());

    std::string file_data;
    std::string line;
    while (std::getline(file, line))
    {
        //file_data.append(line);
        std::cout << line << "1" << "\n";
    }

    std::cout << file.rdbuf();

    char cstr[file_data.size() + 1];
    strcpy(cstr, file_data.c_str());

    printf("\n");
    printf("Got this far");
    printf(cstr);
    printf("%d", file_data.size());
    printf("\n");

    jsonDocument = new rapidjson::Document();
    jsonDocument->Parse(cstr);

    printf("Got this far aaaaaaaaaaaaaaaaaaaaaaaaaa");
    //parseFile(nlohmann::json::parse(data));

    file.close();*/
    return NULL;
}
