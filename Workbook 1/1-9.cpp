#include <bits/stdc++.h>
using namespace std;

struct Node{
    int l;
    int r;
    Node* left;
    Node* right;
};

void createRangeTree(Node*& root, int l, int r){
    root = new Node();
    if ((r - l) == 1){
        root->l = l;
        root->r = r;
    }
    else{
        root->l = l;
        root->r = r;

        createRangeTree(root->left, l, (l + r) / 2);
        createRangeTree(root->right, (l + r) / 2, r);
    }
}


void printTree(Node* root, int order){
    if (root){
        switch (order){
            case -1:
                cout << root->l << ' ' << root->r << " | ";
                printTree(root->left, order);
                printTree(root->right, order);
                break;
            case 0:
                printTree(root->left, order);
                cout << root->l << ' ' << root->r << " | ";
                printTree(root->right, order);
                break;
            case 1:
                printTree(root->left, order);
                printTree(root->right, order);
                cout << root->l << ' ' << root->r << " | ";
                break;
        }   
    }
}


int countX(Node* root, int x){
    if (!root){
        return 0;
    }

    if (root->l <= x && root->r >= x){
        return countX(root->left, x) + countX(root->right, x) + 1;
    }
    return countX(root->left, x) + countX(root->right, x);
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

    createRangeTree(root, 1, 6);

    cout << "Прямой обход: ";
    printTree(root, -1);

    cout << "\n\nСимметричный обход: ";
    printTree(root, 0);
    
    cout << "\n\nОбратный обход обход: ";
    printTree(root, 1);


    cout << "\n\nТочка 2 встречется в дереве отрезков " << countX(root, 2) << " раз" << endl;
    
    deleteTree(root);
    printTree(root, -1);
}