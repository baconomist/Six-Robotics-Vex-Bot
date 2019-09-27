//
// Created by Lucas on 9/20/2019.
//

#ifndef VEXROBOT_AUTON_PATH_PARSER_H
#define VEXROBOT_AUTON_PATH_PARSER_H

#include "main.h"

class AutonPathNode
{

};

class AutonPathParser
{
public:
    AutonPathParser(FILE* sd_auton_file);


private:
    void parseFile();

};

#endif //VEXROBOT_AUTON_PATH_PARSER_H
