#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    string color;
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
        cout << setw(depth * 6) << prefix << root->data << "(" << root->color << ")" << endl;
        printTree(root->left, depth + 1, '\\');
    }
}

bool checkRedBlackProperties(Node* root, int blackCount = 0, int pathBlackCount = -1, bool& rule2 = *(new bool(true)), bool& rule3 = *(new bool(true)), bool& rule4 = *(new bool(true))) {
    if (!root) return true;
    
    if (root->color == "BLACK") blackCount++;
    
    if (root->color == "RED") {
        if ((root->left && root->left->color == "RED") || (root->right && root->right->color == "RED"))
            rule3 = false; // Два красных узла подряд
    }
    
    if (!root->left && !root->right) {
        if (pathBlackCount == -1)
            pathBlackCount = blackCount;
        else if (blackCount != pathBlackCount)
            rule4 = false; // Разное число черных узлов в пути
    }
    
    return checkRedBlackProperties(root->left, blackCount, pathBlackCount, rule2, rule3, rule4) &&
           checkRedBlackProperties(root->right, blackCount, pathBlackCount, rule2, rule3, rule4);
}

Node* insert(Node* root, int value, string color = "RED"){
    if (!root){
        Node* new_node = new Node;
        new_node->data = value;
        new_node->color = color;
        return new_node;
    }

    if (value < root->data)
        root->left = insert(root->left, value, color);
    else if (value > root->data)
        root->right = insert(root->right, value, color);
    else
        return root;

    root->height = getHeight(root);
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
    
    root = insert(root, 8, "BLACK");
    root = insert(root, 4, "RED");
    root = insert(root, 12, "RED");
    root = insert(root, 2, "BLACK");
    root = insert(root, 6, "BLACK");
    root = insert(root, 10, "BLACK");
    root = insert(root, 14, "RED");
    
    printTree(root);
    
    bool rule2 = (root->color == "BLACK");
    bool rule3 = true;
    bool rule4 = true;
    
    checkRedBlackProperties(root, 0, -1, rule2, rule3, rule4);
    
    cout << "Проверка свойств красно-черного дерева:\n";
    cout << "1. Каждый узел либо красный, либо черный: Всегда выполняется.\n";
    cout << "2. Корень всегда черный: " << (rule2 ? "Выполняется" : "Не выполняется") << "\n";
    cout << "3. У красного узла оба потомка черные: " << (rule3 ? "Выполняется" : "Не выполняется") << "\n";
    cout << "4. Все пути от корня до листьев содержат одинаковое количество черных узлов: " << (rule4 ? "Выполняется" : "Не выполняется") << "\n";
    
    deleteTree(root);
}
