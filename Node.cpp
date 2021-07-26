//
// Created by master on 23.07.2021.
//

#include "Node.h"

Node::Node(int _value, char _c_value, Node *_right, Node *_left, Node *_par, Node *_next) {
    value = _value;
    c_value = _c_value;
    par = _par;
    left = _left;
    right = _right;
    next = _next;
}

Node &Node::operator=(const Node* node) {
    if(this == node)
        return *this;
    this->right = node->right;
}


