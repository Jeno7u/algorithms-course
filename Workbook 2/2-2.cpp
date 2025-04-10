#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    int height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
};

int getHeight(Node* root){
    if (!root)
        return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

int getBalance(Node* root){
    if (!root)
        return 0;
    return getHeight(root->right) - getHeight(root->left);
}

void printTree(Node* root, int depth = 0, char prefix = ' ') {
    if (root != nullptr) {
        printTree(root->right, depth + 1, '/');
        cout << setw(depth * 6) << prefix << root->data << "(" << getBalance(root) << ")" << endl;
        printTree(root->left, depth + 1, '\\');
    }
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; 
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; 
}

Node* insert(Node* root, int value){
    if (!root){
        Node* new_node = new Node;
        new_node->data = value;
        return new_node;
    }

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        return root;

    root->height = getHeight(root);

    int balance = getBalance(root);
    if (balance < -1 && value < root->left->data){ // LL case
        return rightRotate(root);
    }
    else if (balance > 1 && value > root->right->data){ // RR case
        return leftRotate(root);
    }
    else if (balance < -1 && value > root->left->data){ // LR case
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    else if (balance > 1 && value < root->right->data){ // RL case
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void deleteTree(Node*& root){
    if (root){
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
}

int main(){
    Node* root = nullptr;

    root = insert(root, 8);
    root = insert(root, 9);
    root = insert(root, 10);
    root = insert(root, 11);
    root = insert(root, 7);
    root = insert(root, 6);
    printTree(root);

    deleteTree(root);
}