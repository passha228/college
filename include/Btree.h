//
// Created by passha228 on 5/10/21.
//
#ifndef CLASS_TREE_BTREE_H
#define CLASS_TREE_BTREE_H
#include "Node.h"

struct Trunk;

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
    virtual void Add(Node * node);
    virtual int Max();

    virtual int Min();

    virtual Node* Search(int value);

    void Del(int);

    void Print();
    //??????????
    ~Btree();
protected:
    Node* create_node(Node* tmp, Node* pp);
    Node* root;
    void delete_root();
    static void change_link(Node* p, Node* s);
    static void del_node1(Node* node);
    static void del_node2(Node* node);
    Node* detour_preOrder(Node* node);
    Node* detour_inOrder(Node* node);
    Node* detour3_postOrder(Node* node);
    private:
    Node* search(Node *p1, int _key);
    static void deleting(Node* node);
    void constructor1(vector<int>);
    int max(Node* node, int max);
    int min(Node* node, int max);
    void add(int value, Node* node);

    void print_tree(const std::string& prefix, const Node* node, bool isLeft);


};

#endif