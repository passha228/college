#include <iostream>
#include "Btree.h"
#include "STree.h"

/*template <class T>
void test();*/

using namespace std;


int main() {

//    Btree tree(10);
//    tree.Add(20);
//    cout << tree.Max();
//    Btree tree1 = tree;
//    cout << tree1.Max() << endl;
//    cout << tree.Min();

    int mas[7] = {10,15,20,5,7,8,35};
    STree tree(mas, 7);
    STree tree1;
    cout << tree.Min() << endl;
    cout << tree.Max() << endl;
    tree1 = tree;
    //tree.Del(35);
    tree.Del(5);
    return 0;
}




/*template <class T>
void test(T test, T test1)
{
    test.Add(10);
    

}*/