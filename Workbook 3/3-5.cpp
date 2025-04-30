#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};


void printTree(Node* root, int depth = 0, char prefix = ' ') {
    if (root != nullptr) {
        printTree(root->right, depth + 1, '/');
        cout << setw(depth * 4) << prefix << root->data << endl;
        printTree(root->left, depth + 1, '\\');
    }
}

bool isMaxHeap(Node* root){
    if (!root) return true;

    if (root->left && root->left->data > root->data)
        return false;

    if (root->right && root->right->data > root->data)
        return false;

    return isMaxHeap(root->left) && isMaxHeap(root->right);
}

bool isMinHeap(Node* root){
    if (!root) return true;

    if (root->left && root->left->data < root->data)
        return false;

    if (root->right && root->right->data < root->data)
        return false;

    return isMinHeap(root->left) && isMinHeap(root->right);
}
bool isHeap(Node* root){
    if (!root)
        return true;

    if (isMinHeap(root) || isMaxHeap(root))
        return true;

    return false;
}

int main(){
    Node* root;
    root = new Node{18, nullptr, nullptr};
    root->left = new Node{14, nullptr, nullptr};
    root->right = new Node{10, nullptr, nullptr};
    root->left->left = new Node{8, nullptr, nullptr};
    root->left->right = new Node{3, nullptr, nullptr};
    root->right->left = new Node{12, nullptr, nullptr};

    printTree(root);

    if (isHeap(root)){
        cout << "\nThis tree is valid heap" << endl;
    }
    else{
        cout << "\nThis tree is NOT valid heap" << endl;
    }
}