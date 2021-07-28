//
// Created by passha228 on 5/10/21.
//
#ifndef CLASS_TREE_NODE_H
#define CLASS_TREE_NODE_H
#include <iostream>
#include <vector>

using namespace std;
class Btree;
class STree;
class AVL;

class Node
{
public:
	explicit Node(int _value = 0, Node* _right = nullptr, Node* _left = nullptr, Node* _par = nullptr, unsigned char _height = 0){
		value = _value; par = _par; left = _left; right = _right; height = _height;
	}
	friend class Btree;
	friend class STree;
	friend class AVL;

private:
    int value;
    Node* right;
    Node* left;
    Node* par;
    unsigned char height;
};

#endif