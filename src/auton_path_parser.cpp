//
// Created by Lucas on 9/20/2019.
//

#include "auton_path_parser.h"

// nlohmann::json data;
AutonPathParser::AutonPathParser (std::string file_path) {
  std::ifstream readfile(file_path);
  // readfile >> data;
  parseFile();
}

void AutonPathParser::parseFile () {
  // std::cout << data;
}
