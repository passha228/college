#ifndef CLASS_TREE_BTREE_H
#define CLASS_TREE_BTREE_H
#include "Node.h"


class Btree
{
public:

    Btree();

    string Haffman(const string& s);

    ~Btree();
protected:
    Node* root{};

private:
    //разбить строку на отдельные символы, подсчитать их кол-во, закинуть их в список вшитый в дерево
    //используется рекурсивное определение
    void Split(const string& s);
    Node* split(const int * mas, int i);

    //разбиение на дерево
    void haffman();
    Node* detour3_postOrder(Node* node);
    void preOrder(Node*node, Node*& save);
    Node* not_leaf(Node*& node, Node*& where);
    void sort();

    //делаем пару символ -> двоичный код
    void bin(Node*, map<const char, string>& a, const string& s);

    //кодируем строку
    string coding(map<const char, string>, const string&);
};



#endif