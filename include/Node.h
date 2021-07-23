#ifndef CLASS_TREE_NODE_H
#define CLASS_TREE_NODE_H
#include <iostream>
#include <vector>
#include "string"
#include <iostream>
#include <set>
#include <map>

using namespace std;
class Btree;
class STree;
class AVL;

class Node
{
public:
	explicit Node(int _value = 0,char _c_value = 0, Node* _right = nullptr, Node* _left = nullptr, Node* _par = nullptr,Node* _next = nullptr, unsigned char _height = 0){
		value = _value;
        //if (static_cast<int>(_c_value) != 0)
            //c_value.insert(_c_value);
		par = _par;
		left = _left;
		right = _right;
		next = _next;
		height = _height;
	}
	friend class Btree;

    void split(string s);

private:
    unsigned int value;
    set<char> char_set;
    char c_value;
    Node* right;
    Node* left;
    Node* par;
    Node* next;
    unsigned char height;
};

#endif