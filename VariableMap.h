#ifndef VARIABLE_MAP_H
#define VARIABLE_MAP_H

#include <string>
#include <memory>
#include <map>

class VariableMap {
public:
    static std::shared_ptr<std::map<std::string, bool>> instance;
    static void printVariableMap(const std::map<std::string, bool>& varMap);
    static void init();
};

#endif
