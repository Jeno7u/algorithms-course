#include <bits/stdc++.h>
using namespace std;

struct Node{
    string name;
    vector<string> phones;
    Node* left;
    Node* right;
};

void insert(Node*& root, const string& name, const string& phone){
    if (!root){
        Node* new_node = new Node;
        new_node->name = name;
        new_node->phones.push_back(phone);
        new_node->left = nullptr;
        new_node->right = nullptr;
        root = new_node;
    }
    else if (root->name > name){
        insert(root->left, name, phone);
    }
    else if (root->name < name){
        insert(root->right, name, phone);
    }
    else{
        root->phones.push_back(phone);
    }
}

void printTree(Node* root, const int order){
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

Node* findNode(Node* root, const string* name){
    if (root == nullptr || root->name == *name){
        return root;
    }
    else if (*name < root->name){
        return findNode(root->left, name);
    }
    return findNode(root->right, name);

}

void deleteNode(Node*& root, const string& name){
    if (root == nullptr){
        return;
    }

    if (name < root->name){
        deleteNode(root->left, name);
    }
    else if (name > root->name){
        deleteNode(root->right, name);
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
                root->name = max->name;
                deleteNode(max, name);
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
    Node* root = nullptr;

    cout << "Консольное приложение: \"Телефонная книга\"!" << endl;
    while (1){
        int action;
        cout << "\nВыберите действие:" << endl;
        cout << "\t1. Найти по имени номер(а) телефона(ов)" << endl;
        cout << "\t2. Записать номер" << endl;
        cout << "\t3. Удалить номер" << endl;
        cin >> action;

        string name;
        switch (action){
            case 1: {
                cout << "Введите фамилию и имя: ";
                cin.ignore();
                getline(cin, name);
                
                Node* result = findNode(root, &name);
                if (result && (result->phones.size() != 0)){
                    cout << "Номера телефона " << name << ": ";
                    if (result->phones.size() == 1){
                        cout << result->phones[0] << endl;
                    }
                    else{
                        for (int i = 0; i < result->phones.size() - 1; i++){
                            cout << result->phones[i] << ", ";
                        }
                        cout << result->phones[result->phones.size() - 1] << endl;
                    }
                }
                else{
                    cout << "\nНомера телефонов не найдены...\n\n" << endl;
                }
                break;
            }
            case 2: {
                string phone;
                cout << "Введите фамилию и имя: ";
                cin.ignore();
                getline(cin, name);
                cout << "Введите номер телефона:";
                cin >> phone;
                
                insert(root, name, phone);
                cout << "\nНомер телефона успешно сохранен!" << endl;
                break;
            }
            case 3: {
                cout << "Введите фамилию и имя: ";
                cin.ignore();
                getline(cin, name);

                deleteNode(root, name);
                cout << "\nНомер телефона успешно удалён!" << endl;
                break;
            }
        }
    }
}