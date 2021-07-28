#include "include/Btree.h"
#include <random>


////////////////////////////////////////////////////////////////////
//						конструкторы 							////
////////////////////////////////////////////////////////////////////

Btree::Btree()
{
	root = nullptr;
}

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
    Node *p=nullptr;
    if (p1->value == _key) return p1;
    if (p1->left) p=search(p1->left, _key);
    if (p) return p;
    if (p1->right) p=search(p1->right, _key);
    return p;
}

Node* Btree::Search(int _key)
{
    if (!root) return nullptr;
    Node *p=nullptr;
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
        pr->left == node ? pr->left : pr->right = nullptr;
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

Node* Btree::detour3_postOrder(Node* node)
{
    if (node == nullptr) return nullptr;
    detour3_postOrder(node->left);
    detour3_postOrder(node->right);
    delete node;
    node = nullptr;
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
    Node *p=nullptr;
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

void sort(Node*);

void Btree::haffman() {
    //сортировка
    this->sort();
    while(this->root->next != nullptr)
    {
        //если оба узла листья
        if(this->root->c_value != 0 && this->root->next->c_value != 0) {
            //создание дерева
                //левое поддерево
            this->root->left = new Node;
            this->root->left->value = this->root->value;
            this->root->left->c_value = this->root->c_value;

                //правое поддерево
            this->root->right = new Node;
            this->root->right->value = this->root->next->value;
            this->root->right->c_value = this->root->next->c_value;
        }
        //если следующий элемент лист
        else if(this->root->next->c_value != 0)
        {
            //левое поддерево
            this->not_leaf(root, root->left);

            //правое поддерево
            this->detour3_postOrder(this->root->right);
            this->root->right = new Node;
            this->root->right->value = this->root->next->value;
            this->root->right->c_value = this->root->next->c_value;
        }
        //если корень - лист
        else if(this->root->c_value != 0)
        {
            //левое поддерево
            this->not_leaf(root->next, root->left);
            //правое поддерево
            this->root->right = new Node;
            this->root->right->value = root->value;
            this->root->right->c_value = this->root->c_value;
        }
        //если оба не лист
        else
        {
            this->not_leaf(root, root->left);
            this->not_leaf(root->next, root->right);
        }
        this->root->c_value = 0;
        this->root->value+=this->root->next->value;
        Node *node = this->root->next->next;
        delete this->root->next;
        this->root->next = node;
        this->sort();
    }
}

void Btree::sort(){
    //сортировка по адресу
    Node *new_root = nullptr;

    while ( root != nullptr )
    {
        Node *node = root;
        root = root->next;

        if ( new_root == nullptr || node->value < new_root->value )
        {
            node->next = new_root;
            new_root = node;
        }
        else
        {
            Node *current = new_root;
            while ( current->next != nullptr && node->value >= current->next->value)
            {
                current = current->next;
            }

            node->next = current->next;
            current->next = node;
        }
    }
    root = new_root;
}

void Btree::bin(Node* node, map<const char, string>& a, string s) {
    if (node == nullptr)
        return;
    bin(node->left, a, s + '0');
    bin(node->right, a, s + '1');
    //вполне достаточно node->c_value != 0, однако для надежности еще проверяю левый правый узлы
    if (node->c_value != 0 && node->right == nullptr && node->left == nullptr)
    {
        a.insert(make_pair(node->c_value, s));
    }

}

void Btree::Split(const string& s) {
    int mas[256] = {0};
    for(auto i: s)
    {
        mas[i]++;
    }
    //далее превращаем mas в Node
    int i = 1;
    root = new Node;
    for(i; i < 256; i++)
        if(mas[i])
        {
            this->root->value = mas[i];
            this->root->c_value = static_cast<char>(i);
            break;
        }

    root->next = split(mas, ++i);
//    for(Node *a = root; a != nullptr; a = a->next)
//    {
//        cout << a->value << ' ' << a->c_value << '\n';
//    }
}

Node* Btree::split(const int* mas, int i) {
    if (i >= 256)
    {
        return nullptr;
    }
    Node *node = nullptr;
    for (i; i < 256; i++)
    {
        if(mas[i]) {
            node = new Node;
            node->c_value = static_cast<char>(i);
            node->value = mas[i];
            break;
        }
    }
    if(i < 256 && node != nullptr)
        node->next =  split(mas, ++i);
    return node;
}



//сделать рекурсивное определение, тупое копирование адресов не сработал
Node* Btree::not_leaf(Node*& node, Node*& where)
{
    Node* new_node = nullptr;
    this->preOrder(node, new_node);
    this->detour3_postOrder(where);
    where = new_node;
    return nullptr;
}

void Btree::preOrder(Node *node, Node*& save) {
    if (node == nullptr)
        return;
    if(save == nullptr)
        save = new Node;
    save->value = node->value;
    save->c_value = node->c_value;
    preOrder(node->left,save->left);
    preOrder(node->right,save->right);
}

string Btree::Haffman(const string& s) {
    //вытащили все символы и узнали их длину
    this->Split(s);
    //разбили в дерево в зависимости от длины символа
    this->haffman();
    //составить пару символ -> бинарный код
    map<const char, string> a;
//    for(int i = 0; i < 256; i++)
//    {
//        if(mas[i] != 0) {
//            a.insert(make_pair(static_cast<const char>(mas[i]), ""));
//        }
//
//    }
//    for(const auto& i: a)
//    {
//        cout << i.first << ' ' << i.second;
//    }
    this->bin(root, a, "");
    for(auto i : a)
    {
        cout << i.first << ' ' << i.second << '\n';
    }
    cout << s << '\n';
    //вернуть закодированное сообщение
    return this->coding(a, s);
}

string Btree::coding(map<const char, string> a, const string& s) {
    string new_string;
    for(const char i : s)
    {
        new_string+=a[i];
    }
    return new_string;
}
