#include <bits/stdc++.h>
using namespace std;

enum Color { RED, BLACK };

struct Node{
    int data;
    Color color;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
};

void rotateLeft(Node*& root, Node*& pt) {
    Node* pt_right = pt->right;
    pt->right = pt_right->left;
    if (pt->right)
        pt->right->parent = pt;
    pt_right->parent = pt->parent;
    if (!pt->parent)
        root = pt_right;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
    else
        pt->parent->right = pt_right;
    pt_right->left = pt;
    pt->parent = pt_right;
}

void rotateRight(Node*& root, Node*& pt) {
    Node* pt_left = pt->left;
    pt->left = pt_left->right;
    if (pt->left)
        pt->left->parent = pt;
    pt_left->parent = pt->parent;
    if (!pt->parent)
        root = pt_left;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
    else
        pt->parent->right = pt_left;
    pt_left->right = pt;
    pt->parent = pt_left;
}

void fixViolation(Node*& root, Node*& pt) {
    Node* parent_pt = nullptr;
    Node* grand_parent_pt = nullptr;
    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
        if (parent_pt == grand_parent_pt->left) {
            Node* uncle_pt = grand_parent_pt->right;
            if (uncle_pt && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->right) {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        } else {
            Node* uncle_pt = grand_parent_pt->left;
            if (uncle_pt && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt->left) {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }
    root->color = BLACK;
}

Node* insert(Node*& root, Node*& pt) {
    if (!root) return pt;
    if (pt->data < root->data) {
        root->left = insert(root->left, pt);
        root->left->parent = root;
    } else if (pt->data > root->data) {
        root->right = insert(root->right, pt);
        root->right->parent = root;
    }
    return root;
}

void insertValue(Node*& root, int data) {
    Node* pt = new Node{data, RED};
    root = insert(root, pt);
    fixViolation(root, pt);
}

void printTree(Node* root, int depth = 0, char prefix = ' ') {
    if (root) {
        printTree(root->right, depth + 1, '/');
        cout << setw(depth * 6) << prefix << root->data << "(" << (root->color == RED ? "R" : "B") << ")" << endl;
        printTree(root->left, depth + 1, '\\');
    }
}

int main() {
    Node* root = nullptr;
    insertValue(root, 8);
    insertValue(root, 4);
    insertValue(root, 12);
    insertValue(root, 2);
    insertValue(root, 6);
    insertValue(root, 10);
    printTree(root);
    cout << "\n\n";
    insertValue(root, 1);
    insertValue(root, 0);
    printTree(root);
}
