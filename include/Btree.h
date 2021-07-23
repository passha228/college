#ifndef CLASS_TREE_BTREE_H
#define CLASS_TREE_BTREE_H
#include "Node.h"
#include <map>

struct Trunk;

class Btree
{
public:

    Btree();

    explicit Btree(map<char, int>);

    Btree& operator=(const Btree& tree);

    void Add_after(int value, char c_value, char after_c_value);

    virtual void Add(int value);

    virtual Node* Search(int value);

    virtual  Node* Search(char);

    void merge(int, char, int, char);
    void Del(int);
    void Print();

    void print_tree(Node* n, Trunk *prev, bool isLeft);

    void haffman(map<char,int> m);
    //??????????
    ~Btree();
protected:
    virtual Node* create_node(map<char, int>::iterator i, map<char, int>);
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

    Node* search(Node*, char);
    void add(int value, Node* node);
};



#endif