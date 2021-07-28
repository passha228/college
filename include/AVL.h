//
// Created by passha228 on 5/10/21.
//

#ifndef CLASS_TREE_AVL_H
#define CLASS_TREE_AVL_H

#include "STree.h"


class AVL :public STree{
public:
    AVL();
    AVL(int);
    AVL(int*,int);
    AVL(vector<int>);

    void Add(int);

private:
    unsigned char height;
    unsigned char Height(Node* p);
    void fix_height(Node* p);
    int bfactor(Node* p);
    Node * rotateR(Node*p);
    Node * rotateL(Node*p);
    Node * balance(Node* p);
    Node* add(Node*,int) override;
};


#endif //CLASS_TREE_AVL_H
