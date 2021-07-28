#include "include/Btree.h"
#include <random>


////////////////////////////////////////////////////////////////////
//						конструктор 							////
////////////////////////////////////////////////////////////////////

Btree::Btree()
{
	root = nullptr;
}



Btree::~Btree()
{
    if(this->root != nullptr)
        detour3_postOrder(root);
}

Node* Btree::detour3_postOrder(Node* node)
{
    if (node == nullptr) return nullptr;
    detour3_postOrder(node->left);
    detour3_postOrder(node->right);
    delete node;
    node = nullptr;
}


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

void Btree::bin(Node* node, map<const char, string>& a, const string& s) {
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
