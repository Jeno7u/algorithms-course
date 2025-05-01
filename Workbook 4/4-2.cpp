#include <iostream>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

TrieNode* root = new TrieNode();

void insert(const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        int index = ch - 'a';
        if (node->children[index] == nullptr) {
            node->children[index] = new TrieNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

bool hasChildren(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            return true;
        }
    }
    return false;
}

void search(const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        int index = ch - 'a';
        if (node->children[index] == nullptr) {
            cout << "Слово: " << word << " не существет в Trie" << endl;
            return;
        }
        node = node->children[index];
    }
    cout << "Слово: " << word << " существет в Trie" << endl;
}

void deleteWord(const string& word) {
    TrieNode* node = root;
    vector<TrieNode*> nodes = {root}; // сохраняем список прошедших node

    // заполняем nodes и проверяем наличие слова
    for (char ch : word) {
        int index = ch - 'a';
        if (node->children[index] == nullptr) {
            cout << "Слово: " << word << " не существет в Trie" << endl;
            return;
        }
        node = node->children[index];
        nodes.push_back(node);
    }
    
    // обьяевляем последнее слово удаленным
    nodes.back()->isEndOfWord = false;


    // ну и снизу вверх через nodes удаляем элементы в Trie
    for (int i = word.size(); i >= 0; i--) {
        int index = word[i - 1] - 'a';

        if (!hasChildren(nodes[i]) && !nodes[i]->isEndOfWord) {
            delete nodes[i];
            nodes[i - 1]->children[index] = nullptr;
        }
        else {
            break;
        }
    }
}

int main() {
    insert("hello");
    insert("word");
    insert("heaven");
    insert("heavy");
    insert("heat");
    
    string word = "heaven";

    search(word);

    cout << "Удаляем " << word << "..." << endl;
    deleteWord(word);

    search(word);
    
    return 0;
}