#include "include/Btree.h"
#include <random>


////////////////////////////////////////////////////////////////////
//						конструкторы 							////
////////////////////////////////////////////////////////////////////

Btree::Btree()
{
	root = nullptr;
}

Btree::Btree(map<char, int> m) {
    auto i = m.begin();
    root = new Node(i->second,i->first);
    i++;
    root->next = create_node(i,m);
}

//ôóíêöèÿ äëÿ êîïèðîâàíèÿ äåðåâà
Node* Btree::create_node(map<char, int>::iterator i, map<char, int> m)
{	if (i == m.end())
        return nullptr;
	Node* t = new Node(i->second,i->first);
	i++;
	t->next = create_node(i, m);
	return t;
}


////////////////////////////////////////////////////////////////////
//						перегрузки операторов					////
////////////////////////////////////////////////////////////////////

//Btree& Btree::operator=(const Btree& tree)
//{
//    if(root!= nullptr)
//	    this->~Btree();
//    root = new Node(tree.root->value);
//    root->left = create_node(tree.root->left, root);
//    root->right = create_node(tree.root->right, root);
//	return *this;
//}


////////////////////////////////////////////////////////////////////
//				            поиск								////
////////////////////////////////////////////////////////////////////


Node* Btree::search(Node* p1, int _key)
{
    Node *p=0;
    if (p1->value == _key) return p1;
    if (p1->left) p=search(p1->left, _key);
    if (p) return p;
    if (p1->right) p=search(p1->right, _key);
    return p;
}

Node* Btree::Search(int _key)
{
    if (!root) return 0;
    Node *p=0;
    if (root->value == _key) return root;
    if (root->left) p=search(root->left, _key);
    if (p) return p;
    if (root->right) p=search(root->right, _key);
    return p;
}
////////////////////////////////////////////////////////////////////
//				удаление ключа									////
////////////////////////////////////////////////////////////////////

void Btree::Del(int value)
{
    Node *p = Search(value);
    if (p==root)  delete_root();
    else if (!p->left || !p->right)
        del_node1(p);
    else
        del_node2(p);
    delete p;
}


void Btree::change_link(Node* p, Node* s)
{
	Node* pr = p->par;  // pr - ïðåäîê p
	s->left = p->left; s->right = p->right;  	//1
	s->left->par = s;  s->right->par = s;		//2
	s->par = pr;					//3
	if (pr->left == p) pr->left = s;		//4
	else  pr->right = s;
}

void Btree::del_node1(Node* node)
{
	Node* pr = node->par;
	if (!node->left && !node->right)     // p - ëèñò
		if (pr->left == node) pr->left = 0;
		else  pr->right = 0;
	else  // p – íå ëèñò, ó íåãî 1 ïîòîìîê
	{
		Node* s;
		if (node->left) s = node->left; else s = node->right;
		//changeLink(p, s);
		if (pr->left == node) pr->left = s;
		else  pr->right = s;
		s->par = pr;
	}
}

void Btree::del_node2(Node* p)
{
	Node* s, * t, * pr = p->par;
	s = p->right;
	if (!s->left)
	{
		s->left = p->left; s->left->par = s;
		if (pr->left == p) pr->left = s;
		else  pr->right = s;
		s->par = pr;
	}
	else   // ó s åñòü ëåâîå ïîääåðåâî
	{
		while (s->left) s = s->left;
		del_node1(s); // îñâîáîæäàåì s îò îáÿçàòåëüñòâ
		change_link(p, s); // ìåíÿåì ñâÿçè
	}
}
void Btree::delete_root() {
    if(root->left == nullptr && root->right == nullptr)
        delete root;
    else if(root->left == nullptr && root->right != nullptr) {
        Node* node = root->right;
        delete root;
        root = node;
        root->par = nullptr;
    }
    else if(root->right == nullptr && root->left != nullptr) {
        Node* node = root->left;
        delete root;
        root = node;
        root->par = nullptr;
    }
    else
    {
        Node *node = root;
        while(node->right != nullptr)
        {
            node->value = node->right->value;
            node=node->right;
        }
        delete node;
    }

}

Btree::~Btree()
{

    while(root ->left != nullptr || root->right != nullptr)
    {
        if(root->left!=nullptr)
            this->Del(root->left->value);
        if(root->right!=nullptr)
            this->Del(root->right->value);
    }
    delete root;
}


////////////////////////////////////////////////////////////////////
//				добавление 										////
////////////////////////////////////////////////////////////////////

void Btree::Add(int value)
{
	if (!root) {
	    root = new Node(value);
	    return; }
	if (!root->left) {
	    root->left = new Node(value);
        root->left->par = root;
	    return;
	}
	if (!root->right) {
	    root->right = new Node(value);
        root->right->par = root;
        return; }
	if (rand() % 2) return add(value, root->left);
	else  return  add(value, root->right);
}

void Btree::add(int value, Node* node)
{
	if (!node->left) {
	    node->left = new Node(value);
        node->right->par = node;
	    return; }
	if (!node->right) {
	    node->right = new Node(value);
        node->right->par = node;
	    return; }
	if (rand() % 2)
	    return add(value, node->left);
	else
	    return  add(value, node->right);
}



Node* Btree::detour3_postOrder(Node* node)
{
	if (node) {
		detour3_postOrder(node->left);
		detour3_postOrder(node->right);
		return node;
	}
	else return nullptr;
}

void Btree::Add_after(int value, char c_value, char after_c_value) {
    Search(after_c_value);

}

Node *Btree::Search(char val) {
    if (!root) return nullptr;
    Node *p= nullptr;
    //if (root->c_value == val) return root;
    if (root->left) p=search(root->left, val);
    if (p) return p;
    if (root->right) p=search(root->right, val);
    return p;
}

Node* Btree::search(Node* p1, char _key)
{
    Node *p=0;
   // if (p1->c_value == _key) return p1;
    if (p1->left) p=search(p1->left, _key);
    if (p) return p;
    if (p1->right) p=search(p1->right, _key);
    return p;
}


/*
 *
 *                                     ВЫВОД
 */
void Btree::Print() {
    print_tree(root, nullptr,false);
}

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;
}


void Btree::print_tree(Node * n, Trunk * prev, bool isLeft) {
        if (n == nullptr) {
            return;
        }

        string prev_str = "    ";
        Trunk *trunk = new Trunk(prev, prev_str);

    print_tree(n->right, trunk, true);

        if (!prev) {
            trunk->str = "---";
        }
        else if (isLeft)
        {
            trunk->str = ".---";
            prev_str = "   |";
        }
        else {
            trunk->str = "`---";
            prev->str = prev_str;
        }

        showTrunks(trunk);
        cout << n->value << endl;

        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = "   |";

        print_tree(root->left, trunk, false);
}

void Btree::haffman(map<char, int> m) {
    while(true)
    {
        
        pair<int, char>  pair1;



        return;
    }
}