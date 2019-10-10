//
// Created by Lucas on 9/20/2019.
//

#ifndef VEXROBOT_AUTON_PATH_PARSER_H
#define VEXROBOT_AUTON_PATH_PARSER_H

#include "main.h"
// #include "json.h"
#include <fstream>

class AutonPathNode
{

};

class AutonPathParser
{
public:
    AutonPathParser(std::string file_path);


private:
    void parseFile();
};

#endif //VEXROBOT_AUTON_PATH_PARSER_H
