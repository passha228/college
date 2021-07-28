//
// Created by passha228 on 5/9/21.
//

#ifndef CLASS_TREE_STREE_H
#define CLASS_TREE_STREE_H
#include "Btree.h"



class STree : public Btree{
public:

    STree();

    explicit STree(int value);

    STree(int* mas, int n);

    explicit STree(vector<int> mas);

    STree(const STree& tree);

    virtual void Add(int val) override;

    int Max() override;

    int Min() override;

    Node* Search(int val) override;
    //~STree();
protected:

private:
    virtual Node* add(Node * node, int val);
};


#endif //CLASS_TREE_STREE_H
