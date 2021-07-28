#ifndef CLASS_TREE_NODE_H
#define CLASS_TREE_NODE_H
#include <iostream>
#include "string"
#include "map"

using namespace std;
class Btree;

class Node
{
    friend class Btree;

public:
	explicit Node(int _value = 0,char _c_value = 0, Node* _right = nullptr, Node* _left = nullptr, Node* _par = nullptr,Node* _next = nullptr);
private:
    int value;
    char c_value;
    Node* right;
    Node* left;
    Node* par;
    Node* next;

};

#endif