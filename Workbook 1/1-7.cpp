#include <bits/stdc++.h>
using namespace std;

struct Node{
    string name;
    vector<string> phones;
    Node* left;
    Node* right;
};

void insert(Node*& root, string* name, string* phone){
    if (!root){
        Node* new_node = new Node;
        new_node->name = *name;
        new_node->phones.push_back(*phone);
        new_node->left = nullptr;
        new_node->right = nullptr;
        root = new_node;
    }
    else if (root->name > *name){
        insert(root->left, name, phone);
    }
    else{
        insert(root->right, name, phone);
    }
}

void printTree(Node* root, int order){
    if (root){
        switch (order){
            case -1:
                cout << root->name << " ";
                printTree(root->left, order);
                printTree(root->right, order);
                break;
            case 0:
                printTree(root->left, order);
                cout << root->name << " ";
                printTree(root->right, order);
                break;
            case 1:
                printTree(root->left, order);
                printTree(root->right, order);
                cout << root->name << " ";
                break;
        }
    }
}

Node* findNode(Node* root, string* name){
    if (root == nullptr || root->name == *name){
        return root;
    }
    else if (*name < root->name){
        return findNode(root->left, name);
    }
    return findNode(root->right, name);

}

// void deleteNode(Node*& root, int value){
//     if (root == nullptr){
//         return;
//     }

//     if (value < root->data){
//         deleteNode(root->left, value);
//     }
//     else if (value > root->data){
//         deleteNode(root->right, value);
//     }
//     else{
//         if (root->left == nullptr && root->right == nullptr){
//             delete root;
//             root = nullptr;
//         }
//         else if (root->left == nullptr){
//             Node* tmp = root;
//             root = root->right;
//             delete tmp;
//         }
//         else if (root->right == nullptr){
//             Node* tmp = root;
//             root = root->left;
//             delete tmp;
//         }
//         else {
//             if (root->left->right != nullptr){
//                 Node* max = root->left;
//                 while (max->right){
//                     max = max->right;
//                 }
//                 root->data = max->data;
//                 deleteNode(max, value);
//             }
//             else{
//                 Node* tmp_right = root->right;
//                 Node* tmp_root = root;
//                 root = root->left;
//                 root->right = tmp_right;
//                 delete tmp_root;
//             }
//         }
//     }
// }

int main(){
    Node* root = nullptr;

    cout << "Консольное приложение: \"Телефонная книга\"!" << endl;
    while (1){
        int action;
        cout << "\nВыберите действие:" << endl;
        cout << "\t1. Найти по имени номер(а) телефона(ов)" << endl;
        cout << "\t2. Записать номер" << endl;
        cout << "\t2. Удалить номер" << endl;
        cin >> action;

        string name;
        switch (action){
            case 1: {
                cout << "Введите фамилию и имя: ";
                cin >> name;
                
                Node result = *(findNode(root, &name));
                if (result.phones.size() != 0){
                    for (int i = 0; i < result.phones.size(); i++){
                        cout << result.phones[i] << endl;
                    }
                }
                else{
                    cout << "\nНомера телефонов не найдены..." << endl;
                }
                break;
            }
            case 2: {
                string phone;
                cout << "Введите фамилию и имя: ";
                cin >> name;
                cout << "\nВведите номер телефона:";
                cin >> phone;
                
                insert(root, &name, &phone);
                cout << "\nНомер телефона успешно сохранен!" << endl;
                break;
            }
        }
    }
}