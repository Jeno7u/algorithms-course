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

int countWords(TrieNode* node) {
    if (node == nullptr) return 0;
    
    int count = 0;
    if (node->isEndOfWord) {
        count++;
    }
    
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            count += countWords(node->children[i]);
        }
    }
    return count;
}

int countWordsWithPrefix(const string& prefix) {
    TrieNode* node = root;
    
    // переход к нужному префиксу
    for (char ch : prefix) {
        int index = ch - 'a';
        if (node->children[index] == nullptr) {
            return 0; // не нашли :(
        }
        node = node->children[index];
    }
    // подсчитываем слова с префикса рекурсивно
    return countWords(node);
}

int main() {
    insert("hello");
    insert("word");
    insert("heaven");
    insert("heavy");
    insert("heat");
    
    string prefix;
    cout << "Введите префикс: ";
    cin >> prefix;
    
    int count = countWordsWithPrefix(prefix);
    cout << "Количество слов с префиксом '" << prefix << "': " << count << endl;
    
    return 0;
}