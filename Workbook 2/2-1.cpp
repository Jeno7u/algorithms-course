#include <bits/stdc++.h>
using namespace std;


struct Node{
    unsigned int data;
    int balance;
    Node* left;
    Node* right;
};

int depthTree(Node* root){
    if (!root){
        return 0;
    }
    return max(depthTree(root->left), depthTree(root->right)) + 1;
}

void setBalance(Node* root){
    if (root){
        root->balance = depthTree(root->right) - depthTree(root->left);
        setBalance(root->left);
        setBalance(root->right);
    }
}

void insert(Node*& root, unsigned int value){
    if (!root){
        Node* new_node = new Node;
        new_node->data = value;
        new_node->left = nullptr;
        new_node->right = nullptr;
        root = new_node;
    }
    else if (root->data > value){
        insert(root->left, value);
    }
    else{
        insert(root->right, value);
    }
}

void printTree(Node* root, int depth = 0, char prefix = ' ') {
    if (root != nullptr) {
        printTree(root->right, depth + 1, '/');
        
        cout << setw(depth * 6) << prefix << root->data << "(" << root->balance << ")" << endl;
        
        printTree(root->left, depth + 1, '\\');
    }
}

int main(){
    Node* root = nullptr;

    insert(root, 50);
    insert(root, 30);
    insert(root, 40);
    insert(root, 20);
    insert(root, 70);
    insert(root, 10);
    insert(root, 8);
    insert(root, 42);

    setBalance(root);
    printTree(root);
}