#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <bitset>
using namespace std;

// Структура узла дерева Хаффмана
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;
    
    HuffmanNode(char ch, int freq) : 
        ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

unordered_map<char, string> huffmanCodes;
unordered_map<char, int> freq;

void buildFrequencyTable(const string& text) {
    for (char ch : text) {
        freq[ch]++;
    }
}

HuffmanNode* buildHuffmanTree() {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    
    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    
    while (pq.size() != 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        
        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }
    
    return pq.top();
}

void generateCodes(HuffmanNode* root, string code) {
    if (!root) return;
    
    if (root->ch != '\0') {
        huffmanCodes[root->ch] = code;
    }
    
    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}

string compress(const string& text) {
    string compressed = "";
    for (char ch : text) {
        compressed += huffmanCodes[ch];
    }
    return compressed;
}

string decompress(HuffmanNode* root, const string& compressed) {
    string decompressed = "";
    HuffmanNode* current = root;
    
    for (char bit : compressed) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        
        if (current->ch != '\0') {
            decompressed += current->ch;
            current = root;
        }
    }
    
    return decompressed;
}

double compressionRatio(const string& original, const string& compressed) {
    double originalBits = original.length() * 8.0;
    double compressedBits = compressed.length();
    return (originalBits - compressedBits) / originalBits * 100.0;
}

void printTree(HuffmanNode* root, string indent = "") {
    if (!root) return;
    
    if (root->ch != '\0') {
        cout << indent << root->ch << " (" << (double)root->freq/freq[root->ch] << ")" << endl;
    } else {
        cout << indent << "* (" << (double)root->freq/freq.begin()->second << ")" << endl;
    }
    
    printTree(root->left, indent + "  ");
    printTree(root->right, indent + "  ");
}

int main() {
    string text;
    cout << "Введите текст, содержащий не менее двух символов: ";
    getline(cin, text);
    
    if (text.length() < 2) {
        cout << "Текст должен содержать не менее двух символов!" << endl;
        return 1;
    }
    
    buildFrequencyTable(text);
    
    cout << "\nПолученный список частот:\n";
    for (auto pair : freq) {
        cout << pair.first << " (" << (double)pair.second/text.length() << ") ";
    }
    
    HuffmanNode* root = buildHuffmanTree();
    generateCodes(root, "");
    
    cout << "\n\nПостроим дерево...\n";
    printTree(root);
    
    string compressed = compress(text);
    
    cout << "\nПриступим к кодировке введенного текста...";
    cout << "\nСжатый текст: " << compressed << endl;
    
    double ratio = compressionRatio(text, compressed);
    cout << "Коэффициент сжатия: " << ratio << "%" << endl;
    
    string decompressed = decompress(root, compressed);
    cout << "Ранее было зашифровано: " << text << endl;
    cout << "Расшифровано: " << decompressed << endl;
    
    return 0;
}