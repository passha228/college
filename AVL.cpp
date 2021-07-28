//
// Created by passha228 on 5/10/21.
//

#include "AVL.h"

AVL::AVL():STree() {
    height=0;
}

AVL::AVL(int val)
{
    Add(val);
}

AVL::AVL(int* mas, int n)
{
   root = new Node(mas[0]);
    for (int i = 1; i < n; i++) {
        Add(mas[i]);
    }
}

AVL::AVL(vector<int> mas)
{
    for(int i : mas)
    {
        Add(mas[i]);
    }
}

//работает только с ненулевыми указателями
int AVL::bfactor(Node* p)
{
    return Height(p->right)-Height(p->left);
}



//может работать и с нулевыми указателями
unsigned char AVL::Height(Node *p) {
        return p?p->height:0;
}

//восстанавливает корректное значение поля height
void AVL::fix_height(Node *p) {
    unsigned char hl = Height(p->left);
    unsigned char hr = Height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

Node* AVL::rotateR(Node* head) {
    Node * newhead = head->left;
    head->left = newhead->right;
    newhead->right = head;
    head->height = 1+std::max(Height(head->left), Height(head->right));
    newhead->height = 1+std::max(Height(newhead->left), Height(newhead->right));
    return newhead;
}

Node * AVL::rotateL(Node *head) {
    Node * newhead = head->right;
    head->right = newhead->left;
    newhead->left = head;
    head->height = 1+std::max(Height(head->left), Height(head->right));
    newhead->height = 1+std::max(Height(newhead->left), Height(newhead->right));
    return newhead;
}

Node *AVL::balance(Node *p) {
    fix_height(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateR(p->right);
        return rotateL(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateL(p->left);
        return rotateR(p);
    }
    return p; // балансировка не нужна
}

void AVL::Add(int k) // вставка ключа k в дерево с корнем p
{
    root = add(root, k);
}

Node* AVL::add(Node*head, int x)
{
    if(head==nullptr){
        Node * temp = new Node(x);
        return temp;
    }
    if(x < head->value)
        head->left = add(head->left, x);
    else if(x > head->value)
        head->right = add(head->right, x);
    head->height = 1 + std::max(Height(head->left), Height(head->right));
    int bal = Height(head->left) - Height(head->right);
    if(bal>1){
        if(x < head->left->value){
            return rotateR(head);
        }else{
            head->left = rotateL(head->left);
            return rotateR(head);
        }
    }else if(bal<-1){
        if(x > head->right->value){
            return rotateL(head);
        }else{
            head->right = rotateR(head->right);
            return rotateL(head);
        }
    }
    return head;
}