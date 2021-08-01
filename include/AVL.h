//
// Created by passha228 on 5/10/21.
//

#ifndef CLASS_TREE_AVL_H
#define CLASS_TREE_AVL_H

#include "STree.h"


class AVL :public STree{
public:
    AVL();
    explicit AVL(int);
    AVL(int*,int);
    explicit AVL(vector<int>);
    void Del(int) override;
    void Add(int) final;

private:
    void parents(Node *);
    unsigned char Height(Node* p);
    void fix_height(Node* p);
    int bfactor(Node* p);
    Node * rotateR(Node*p);
    Node * rotateL(Node*p);
    Node * balance(Node* p);
    Node* add(Node*,int);
    Node* remove(Node*, int);
    Node* findmin(Node* p);
    Node* removemin(Node* p);
};


#endif //CLASS_TREE_AVL_H
