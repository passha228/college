//
// Created by passha228 on 5/10/21.
//
#ifndef CLASS_TREE_BTREE_H
#define CLASS_TREE_BTREE_H
#include "Node.h"



class Btree
{
public:

    Btree();

    explicit Btree(int value);

    Btree(int* mas, int n);

    explicit Btree(vector<int> mas);

    Btree(const Btree& tree);

    Btree& operator=(const Btree& tree);


    virtual void Add(int value);

    virtual int Max();

    virtual int Min();

    virtual Node* Search(int value);

    void Del(int);

    void print2D();
    //??????????
    ~Btree();
protected:
    virtual Node* create_node(Node* tmp, Node* pp);
    Node* root;
    void delete_root();
    static void change_link(Node* p, Node* s);
    static void del_node1(Node* node);
    static void del_node2(Node* node);
    //virtual int detour_preOrder(Node* node, int (Btree::*max)(Node* node, int max));
    //virtual Node* detour_inOrder(Node* node, int (Btree::* search)(Node* node, int max));
    Node* detour3_postOrder(Node* node);
    virtual Node* search(Node *p1, int _key);
private:
    void print2DUtil(Node *root, int space);

    int max(Node* node, int max);
    int min(Node* node, int max);
    void add(int value, Node* node);
};

#endif