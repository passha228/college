#include "include/Btree.h"
#include <random>
#include <ctime>

////////////////////////////////////////////////////////////////////
//						конструкторы 							////
////////////////////////////////////////////////////////////////////

Btree::Btree()
{
	root = nullptr;
}

Btree::Btree(int value)
{
	root = new Node(value);
}

Btree::Btree(int* mas, int n)
{
    vector<int> a;
    for(int i = 0; i < n; i++) {
        a.push_back(mas[i]);
    }
    constructor1(a);
}

Btree::Btree(vector<int> mas)
{
    if(this->root != nullptr)
        this->~Btree();
    constructor1(std::move(mas));
}

Btree::Btree(const Btree& tree)
{
	root = new Node(tree.root->value);
	root->left = create_node(tree.root->left, root);
	root->right = create_node(tree.root->right, root);
}

Node* Btree::create_node(Node* tmp, Node* pp)
{	if (!tmp)
        return nullptr;
	Node* t = new Node(tmp->value, nullptr, nullptr, pp, 0);
	t->left = create_node(tmp->left, t);
	t->right = create_node(tmp->right, t);
	return t;
}

void Btree::constructor1(vector<int> mas) {
    //Node * node = new Node(mas[0]);
    root = new Node(mas[0]);
    int i = 1;
    Node* p = root;
    std::srand(time(nullptr));
    while (i != mas.size())
    {
        if (p->left == nullptr)
        {
            p->left = new Node(mas[i]);
            p->left->par = p;
            i++;
        }
        else if (p->right == nullptr)
        {
            p->right = new Node(mas[i]);
            p->right->par = p;
            i++;
        }
        else
        {
            //ïî÷èòàòü ïðî óëó÷øåííóþ ðàíäîìíîñòü è ðåàëèçîâàòü åå çäåñü
            bool random = rand() % 2;
            random ? p = p->left : p = p->right;
        }
    }
}

////////////////////////////////////////////////////////////////////
//						перегрузки операторов					////
////////////////////////////////////////////////////////////////////

Btree& Btree::operator=(const Btree& tree)
{
    if(&tree == this)
        return *this;
    if(root!= nullptr)
	    this->~Btree();
    root = new Node(tree.root->value);
    root->left = create_node(tree.root->left, root);
    root->right = create_node(tree.root->right, root);
	return *this;
}

bool Btree::operator==(const Btree &tree){

}
////////////////////////////////////////////////////////////////////
//						минимум максимум						////
////////////////////////////////////////////////////////////////////


int Btree::Max()
{
    return max(root);
}

int Btree::max(Node* node)
{
    int _max = node->value;
    int locale1 = _max;
    int locale2 = _max;
    node->left ? locale1 = this->max(node->left) : node->value;
    _max > locale1 ? _max = _max : _max = locale1;
    node->right ? locale2 = this->max(node->right) : 0;
    _max > locale2 ? _max = _max : _max = locale2;
    return _max;
}

int Btree::Min()
{
    return min(root);
}

int Btree::min(Node* node)
{
    int _min = node->value;
    int locale = _min;
    node->left ? locale = this->min(node->left) : 0;
    _min < locale ? _min = _min : _min = locale;
    node->right ? locale = this->min(node->right) : 0;
    _min < locale ? _min = _min : _min = locale;
    return _min;
}


////////////////////////////////////////////////////////////////////
//				            поиск								////
////////////////////////////////////////////////////////////////////


Node* Btree::search(Node* p1, int _key)
{
    Node *p= nullptr;
    if (p1->value == _key) return p1;
    if (p1->left) p=search(p1->left, _key);
    if (p) return p;
    if (p1->right) p=search(p1->right, _key);
    return p;
}

Node* Btree::Search(int _key)
{
    if (!root)
        return nullptr;
    Node *p= nullptr;
    if (root->value == _key)
        return root;
    if (root->left)
        p=search(root->left, _key);
    if (p)
        return p;
    if (root->right) p=search(root->right, _key);
    return p;
}

////////////////////////////////////////////////////////////////////
//				удаление ключа									////
////////////////////////////////////////////////////////////////////

void Btree::Del(int value)
{
    Node *p = Search(value);
    if (!p) {
        cerr << "error";
        return;
    }

    if (p==root) {
        delete_root();
        return;
    }
    else if (!p->left || !p->right)
        del_node1(p);
    else
        del_node2(p);
    delete p;
}


void Btree::change_link(Node* p, Node* s)
{
	Node* pr = p->par;
	s->left = p->left;
	s->right = p->right;
	s->left->par = s;
	s->right->par = s;
	s->par = pr;
	if (pr->left == p)
	    pr->left = s;
	else
	    pr->right = s;
}

void Btree::del_node1(Node* node)
{
	Node* pr = node->par;
	if (!node->left && !node->right)     // p - ëèñò
		if (pr->left == node)
		    pr->left = nullptr;
		else
		    pr->right = nullptr;
	else  // p – íå ëèñò, ó íåãî 1 ïîòîìîê
	{
		Node* s;
		if (node->left)
		    s = node->left;
		else
		    s = node->right;
		//changeLink(p, s);
		if (pr->left == node)
		    pr->left = s;
		else
		    pr->right = s;
		s->par = pr;
	}
}

void Btree::del_node2(Node* p)
{
	Node* s, * pr = p->par;
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
        Node *node1 = node->par;
        delete node;
        node1->right = nullptr;
    }

}

void Btree::deleting(Node* node)
{
    if (node) {
        deleting(node->left);
        deleting(node->right);
        delete node;
    }
    else return;
}

Btree::~Btree()
{
    deleting(root);
}


////////////////////////////////////////////////////////////////////
//				добавление 										////
////////////////////////////////////////////////////////////////////

void Btree::Add(Node * node)
{
    this->Add(node->value);
}

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
        node->left->par = node;
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

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
Node* Btree::detour3_postOrder(Node* node)
{
    if (node == nullptr) return nullptr;
    detour_inOrder(node->left);
    detour_inOrder(node->right);
    //return node;
    //действия
}

Node* Btree::detour_inOrder(Node *node) {
    if (node == nullptr) return nullptr;
    detour_inOrder(node->left);
    //return node;
    //действия
    detour_inOrder(node->right);
}

Node* Btree::detour_preOrder(Node *node) {
    if (node == nullptr) return nullptr;
    //return node;
    //действия
    detour_preOrder(node->left);
    detour_preOrder(node->right);
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
void Btree::Print() {
    print_tree("", root, false);
}


void Btree::print_tree(const std::string& prefix, const Node* node, bool isLeft) {
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "\\--" );

        // print the value of the node
        std::cout << node->value << std::endl;

        // enter the next tree level - left and right branch
        print_tree( prefix + (isLeft ? "|   " : "    "), node->left, true);
        print_tree( prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}
