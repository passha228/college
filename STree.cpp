//
// Created by passha228 on 5/9/21.
//
#include "STree.h"



STree::STree() {
    root = nullptr;
}

STree::STree(int value) {
    root = new Node;
    root->value = value;
}

STree::STree(int *mas, int n) {
    root = new Node;
    root->value=mas[0];
    for(int i = 1; i < n; i++)
    {
        Add(mas[i]);
    }
}

STree::STree(vector<int> mas) {
    root = new Node;
    root->value=mas[0];
    for(int i : mas)
    {
        Add(i);
    }
}

STree::STree(const STree &tree) {
    root = new Node;
    root->value=tree.root->value;
    root->left = Btree::create_node(tree.root->left, root);
    root->right = create_node(tree.root->right, root);
}

void STree::Add(int val) {
    if(root == nullptr) {
        root = new Node;
        root->value = val;
    }
    else if(root->right == nullptr && root->value <= val)
    {
        root->right = new Node;
        root->right->value = val;
        root->right->par=root;
    }
    else if(root->left == nullptr && root->value > val)
    {
        root->left = new Node;
        root->left->value = val;
        root->left->par=root;
    }
    else
    {
        Node *node;
        if(root->value <= val) {
            node = add(root->right, val);
            if(node->value <=val) {
                node->right = new Node;
                node->right->value = val;
                node->right->par = node;
            }
            else
            {
                node->left = new Node;
                node->left->value = val;
                node->left->par = node;
            }
        }
        else {
            node = add(root->left, val);
            if(node->value <=val) {
                node->right = new Node;
                node->right->value = val;
                node->right->par = node;
            }
            else
            {
                node->left = new Node;
                node->left->value = val;
                node->left->par = node;
            }
        }
    }
}

Node* STree::add(Node *node, int val) {
    if(node->right == nullptr && node->value <= val)
    {
        return node;
    }
    else if(node->left == nullptr && node->value > val)
    {
        return node;
    }
    else {
        if (node->value <= val)
            add(node->right, val);
        else
            add(node->left, val);
    }
}

int STree::Max() {
    Node *node = root;
    while(node->right != nullptr)
    {
        node= node->right;
    }
    return node->value;
}

int STree::Min() {
    Node*node = root;
    while(node->left != nullptr)
    {
        node =node->left;
    }
    return node->value;
}

Node *STree::Search(int val) {
    Node *node;
    node = root;
    while(node->value!= val)
    {
        if(node->value <=val)
            node = node->right;
        else
            node = node->left;
    }
    return node;
}
