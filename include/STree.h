//
// Created by passha228 on 5/9/21.
//

#ifndef CLASS_TREE_STREE_H
#define CLASS_TREE_STREE_H
#include "Btree.h"



class [[maybe_unused]] STree : public Btree{
public:

    STree();

    [[maybe_unused]] __attribute__((unused)) explicit STree(int value);

    __attribute__((unused)) STree(int* mas, int n);

    __attribute__((unused)) explicit STree(vector<int> mas);

    __attribute__((unused)) STree(const STree& tree);

    void Add(int val);

    int Max() override;

    int Min() override;

    Node* Search(int val) override;
    //~STree();
protected:
    Node* add(Node * node, int val);
private:

};


#endif //CLASS_TREE_STREE_H
