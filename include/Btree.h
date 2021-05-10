#pragma once
#include "Node.h"
#include "GL/glut.h"


class Btree
{
public:
    //?? ????????? ???????????
    Btree();
    //??????????? ? ??????
    __attribute__((unused)) explicit Btree(int value);
    //??????????? ????? ???????
    __attribute__((unused)) Btree(int* mas, int n);
    //??????????? ????? ??????
    __attribute__((unused)) explicit Btree(vector<int> mas);
    //??????????? ???????????
    __attribute__((unused)) Btree(const Btree& tree);
    //???????? ???????????
    Btree& operator=(const Btree& tree);

    //???????? ????
    virtual void Add(int value);
    //????? ????????? ?????????? ?????
    virtual int Max();
    //????? ????????
    virtual int Min();
    //????? ?????
    virtual Node* Search(int value);
    //???????? ?????
    void Del(int);

    //????? ?? ?????
    static __attribute__((unused)) void Print_tree();

    //??????????
    ~Btree();
protected:
    Node* create_node(Node* tmp, Node* pp);
    Node* root;
    void delete_root();
    static void change_link(Node* p, Node* s);
    static void del_node1(Node* node);
    static void del_node2(Node* node);
    //virtual int detour_preOrder(Node* node, int (Btree::*max)(Node* node, int max));
    //virtual Node* detour_inOrder(Node* node, int (Btree::* search)(Node* node, int max));
    virtual Node* detour3_postOrder(Node* node);
    virtual Node* search(Node *p1, int _key);
private:
    int max(Node* node, int max);
    int min(Node* node, int max);
    void add(int value, Node* node);
};