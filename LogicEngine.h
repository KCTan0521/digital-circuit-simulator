#ifndef LOGIC_ENGINE_H
#define LOGIC_ENGINE_H

#include <string>
#include <memory>
#include <map>
#include "Token.h"
#include "Node.h"

class LogicEngine {
public:
    static bool evaluate(std::shared_ptr<Node> node,  std::map<std::string, bool>& varMap);
};

#endif
