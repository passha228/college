//
// Created by master on 23.07.2021.
//

#include "Node.h"
#include "typeinfo"


void Node::split(string s) {
    map< const char, int> res;
    set<char> a;
    for (char i : s)
    {
        //если такого элемента нет то создаем
        if (res.find(i) == res.end())
        {
            res[i] = 1;
        }
        //если такой элемент есть то увеличиваем
        else
            res[i]++;
    }
    //далее превращаем map в Node
    Node * node1 = new Node;
    auto i = res.begin();
    node1->value = i->second;
    node1->c_value = i->first;
    this->next = node1;
    i++;
    Node *node = new Node;
    node->c_value=i->first;
    node->value = i->second;

    for(auto i = res.begin(); i != res.end(); i++)
    {


    }
}