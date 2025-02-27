#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};

void insert(Node*& root, int value){
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

void printTree(Node* root, int order){
    if (root){
        switch (order){
            case -1:
                cout << root->data << " ";
                printTree(root->left, order);
                printTree(root->right, order);
                break;
            case 0:
                printTree(root->left, order);
                cout << root->data << " ";
                printTree(root->right, order);
                break;
            case 1:
                printTree(root->left, order);
                printTree(root->right, order);
                cout << root->data << " ";
                break;
        }
    }
}

Node* findNode(Node* root, int value){
    if (root == nullptr || root->data == value){
        return root;
    }
    else if (value < root->data){
        return findNode(root->left, value);
    }
    return findNode(root->right, value);

}


int depthTree(Node* root){
    if (!root){
        return 0;
    }

    int left_depth = depthTree(root->left);
    int right_depth = depthTree(root->right);

    return max(left_depth, right_depth) + 1;
}   

void deleteNode(Node*& root, int value){
    if (root == nullptr){
        return;
    }

    if (value < root->data){
        deleteNode(root->left, value);
    }
    else if (value > root->data){
        deleteNode(root->right, value);
    }
    else{
        if (root->left == nullptr && root->right == nullptr){
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr){
            Node* tmp = root;
            root = root->right;
            delete tmp;
        }
        else if (root->right == nullptr){
            Node* tmp = root;
            root = root->left;
            delete tmp;
        }
        else {
            if (root->left->right != nullptr){
                Node* max = root->left;
                while (max->right){
                    max = max->right;
                }
                root->data = max->data;
                deleteNode(max, value);
            }
            else{
                Node* tmp_right = root->right;
                Node* tmp_root = root;
                root = root->left;
                root->right = tmp_right;
                delete tmp_root;
            }
        }
    }
}

int main(){
    srand(time(0));

    Node* root = nullptr;

    int n;
    cin >> n;
    while (n--){
        insert(root, rand() % 101);
    }
    
    cout << "Прямой обход: ";
    printTree(root, -1);

    cout << "\n\nСимметричный обход: ";
    printTree(root, 0);
    
    cout << "\n\nОбратный обход обход: ";
    printTree(root, 1);
    cout << endl;

    cout << "\nГлубина дерева равна: " << depthTree(root) << endl;

    Node* example_node = findNode(root, 12);
    cout << "Элемент со значением 12 находиться на " << example_node << " адресе" << endl;

    cin >> n;
    deleteNode(root, n);
    printTree(root, -1);
    cout << endl;
}