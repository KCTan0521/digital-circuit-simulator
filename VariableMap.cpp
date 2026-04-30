#include "VariableMap.h"
#include <iostream>
#include <string>
#include <memory>
#include <map>

std::shared_ptr<std::map<std::string, bool>> VariableMap::instance = 
    std::make_shared<std::map<std::string, bool>>();

void VariableMap::printVariableMap(const std::map<std::string, bool>& varMap) {
    for (const auto& [var, value] : varMap) {
        std::cout << "Variable: " << var << ", Value: " << value << std::endl;
    }
}
   