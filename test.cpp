#include <iostream>
#include <ctime>
#include "AVL.h"

using namespace std;


int main() {
    cout << "Btree 0,1,2,3,4,5,6,7,8,9\n";
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    Btree tree(a, 10);
    cout << tree.Max() << ' ';
    cout << tree.Min() << '\n';
    Node * node = tree.Search(5);
    tree.Add(node);
    tree.Print();
    cout << '\n';
    //////////////////////////////////////////

    cout << "Stree 0,1,2,3,4,5,6,7,8,9\n";
    STree stree(a, 10);
    STree stree1(stree);

    return 0;
}