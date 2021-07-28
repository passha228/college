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
    string Haffman(const string& s);
    virtual void Add(int value);

    virtual Node* Search(int value);

    virtual  Node* Search(char);

    void Del(int);
    void Print();

    void print_tree(Node* n, Trunk *prev, bool isLeft);



    ~Btree();
protected:
    virtual Node* create_node(map<char, int>::iterator i, map<char, int>);
    Node* root{};
    void delete_root();
    static void change_link(Node* p, Node* s);
    static void del_node1(Node* node);
    static void del_node2(Node* node);

    virtual Node* search(Node *p1, int _key);
private:
    void Split(const string& s);
    void haffman();
    Node* detour3_postOrder(Node* node);
    void preOrder(Node*node, Node*& save);
    Node* not_leaf(Node*& node, Node*& where);
    void sort();
    Node* split(const int * mas, int i);
    void bin(Node*, map<const char, string>& a, string s);
    Node* search(Node*, char);
    void add(int value, Node* node);
    string coding(map<const char, string>, const string&);
};



#endif