#ifndef CLASS_TREE_BTREE_H
#define CLASS_TREE_BTREE_H
#include "Node.h"
#include "map"

struct Trunk;

class Btree
{
public:

    Btree();

    explicit Btree(Node *node);

    void Add_after(int value, char c_value, char after_c_value);

    __attribute__((unused)) virtual void Add(int value);

    virtual Node* Search(int value);

    virtual  Node* Search(char);

    void Del(int);
    void Print();

    void print_tree(Node* n, Trunk *prev, bool isLeft);

    void haffman();
    void Split(string s);
    ~Btree();
protected:
    virtual Node* create_node(map<char, int>::iterator i, map<char, int>);
    Node* root{};
    void delete_root();
    static void change_link(Node* p, Node* s);
    static void del_node1(Node* node);
    static void del_node2(Node* node);
    Node* detour3_postOrder(Node* node);
    virtual Node* search(Node *p1, int _key);
private:

    Node* split(const int * mas, int i);
    map<const char, string> bin();
    Node* search(Node*, char);
    void add(int value, Node* node);
};



#endif