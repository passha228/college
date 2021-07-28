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
	root = new Node(mas[0]);
	int i = 1;
	Node* p = root;
    std::srand(time(nullptr));
	while(i != n)
	{
		if (p->left == nullptr)
		{
			p->left = new Node[mas[i]];
			p->left->par = p;
			i++;
		}
		else if (p->right == nullptr)
		{
			p->right = new Node[mas[i]];
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

Btree::Btree(vector<int> mas)
{
	root = new Node(mas[0]);
	int i = 1;
	Node* p = root;
	std::srand(time(nullptr));
	while (i != mas.size())
	{
		if (p->left == nullptr)
		{
			p->left = new Node[mas[i]];
            p->left->par = p;
			i++;
		}
		else if (p->right == nullptr)
		{
			p->right = new Node[mas[i]];
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

Btree::Btree(const Btree& tree)
{
	root = new Node(tree.root->value);
	root->left = create_node(tree.root->left, root);
	root->right = create_node(tree.root->right, root);
}

//ôóíêöèÿ äëÿ êîïèðîâàíèÿ äåðåâà
Node* Btree::create_node(Node* tmp, Node* pp)
{	if (!tmp)  return nullptr;   // ÿâíàÿ òî÷êà îñòàíîâêè ðåêóðñèè
	Node* t = new Node(tmp->value, nullptr, nullptr, pp, 0);
	t->left = create_node(tmp->left, t);
	t->right = create_node(tmp->right, t);
	return t;
}


////////////////////////////////////////////////////////////////////
//						перегрузки операторов					////
////////////////////////////////////////////////////////////////////

Btree& Btree::operator=(const Btree& tree)
{
    if(root!= nullptr)
	    this->~Btree();
    root = new Node(tree.root->value);
    root->left = create_node(tree.root->left, root);
    root->right = create_node(tree.root->right, root);
	return *this;
}


////////////////////////////////////////////////////////////////////
//						минимум максимум						////
////////////////////////////////////////////////////////////////////


int Btree::Max()
{
    return max(root, root->value);
}

int Btree::max(Node* node, int max)
{
    int _max = node->value;
    if(node)
    {
        int locale = _max;
        node->left ? locale = this->max(node->left, _max) : 0;
        _max > locale ? _max = _max: _max = locale;

        node -> right? locale = this->max(node->right, _max) : 0;
        _max > locale ? _max = _max: _max = locale;
    }
    return _max;
}

int Btree::Min()
{
    return min(root, root->value);
}

int Btree::min(Node* node, int max)
{
    int _min = node->value;
    if(node)
    {
        int locale = _min;
        node->left ? locale = this->min(node->left, _min) : 0;
        _min < locale ? _min = _min: _min = locale;

        node -> right? locale = this->min(node->right, _min) : 0;
        _min < locale ? _min = _min: _min = locale;
    }
    return _min;
}


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

//Node* Btree::detour_inOrder(Node* node, int (Btree::* search)(Node* node, int max))
//{
//	if (node) {
//		detour_inOrder(node->left, search);
//		return node;
//		detour_inOrder(node->right, search);
//	}
//}


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


void Btree::print2DUtil(Node *node, int space)
{
    // Base case
    if (node == nullptr)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(node->right, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = 10; i < space; i++)
        cout<<" ";
    cout<<node->value<<"\n";

    // Process left child
    print2DUtil(node->left, space);
}

// Wrapper over print2DUtil()
void Btree::print2D()
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}