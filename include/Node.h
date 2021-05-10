#pragma once
#include <iostream>
#include <vector>

using namespace std;
class Btree;
class STree;


class Node
{
public:
	explicit Node(int _value = 0, Node* _right = nullptr, Node* _left = nullptr, Node* _par = nullptr, unsigned char _height = 0){
		value = _value; par = _par; left = _left; right = _right; height = _height;
	}
	/*~Node() {
        delete [] this;
	}*/
	friend class Btree;
	friend class STree;
protected:	
	int value;
	Node* right;
	Node* left;
	Node* par;
	unsigned char height;

	static unsigned char Height(Node* p) {
		return p ? p->height : 0;
	}

    __attribute__((unused)) void fix_height()
	{
		unsigned char hl = Height(par->left);
		unsigned char hr = Height(par->right);
		par->height = (hl > hr ? hl : hr) + 1;
	}
private:

};

