#ifndef NODE_H
#define NODE_H

#include <string>
#include <memory>

using namespace std;

struct Node {
    string value;
    shared_ptr<Node> left, right;
    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

#endif