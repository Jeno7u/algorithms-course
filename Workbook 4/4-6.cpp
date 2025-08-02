#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <iomanip>
using namespace std;

// Структура узла дерева Хаффмана
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char ch, int freq) :
        ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

// Компаратор для очереди с приоритетом
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

// Глобальные переменные
unordered_map<char, string> huffmanCodes;
unordered_map<char, int> freq;

// Метод построения таблицы частот
void buildFrequencyTable(const string& text) {
    for (char ch : text) {
        freq[ch]++;
    }
}

// Метод генерации кодов Хаффмана
void generateCodes(HuffmanNode* root, string code) {
    if (!root) return;

    if (root->ch != '\0') {
        huffmanCodes[root->ch] = code;
    }

    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}

// Построение дерева Хаффмана
HuffmanNode* buildHuffmanTree() {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for (auto& pair : freq) {
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

// Метод сжатия
string compress(const string& text) {
    string compressed = "";
    for (char ch : text) {
        compressed += huffmanCodes[ch];
    }
    return compressed;
}

// Метод распаковки
string decompress(HuffmanNode* root, const string& compressed) {
    string decompressed = "";
    HuffmanNode* current = root;

    for (char bit : compressed) {
        current = (bit == '0') ? current->left : current->right;

        if (current->ch != '\0') {
            decompressed += current->ch;
            current = root;
        }
    }

    return decompressed;
}

// Метод расчёта коэффициента сжатия
double compressionRatio(const string& original, const string& compressed) {
    double originalBits = original.length() * 8.0;
    double compressedBits = compressed.length();
    return (originalBits - compressedBits) / originalBits * 100.0;
}

// Удобный вывод символов
string printableChar(char ch) {
    switch (ch) {
        case '\n': return "'\\n'";
        case '\t': return "'\\t'";
        case '\r': return "'\\r'";
        case ' ':  return "' '";
        default:
            if ((unsigned char)ch < 32 || (unsigned char)ch > 126) {
                // Неотображаемый или UTF-8 символ
                return string("'\\x") + to_string((int)(unsigned char)ch) + "'";
            } else {
                return string("'") + ch + "'";
            }
    }
}

// Вывод таблицы частот
void printFrequencies(const string& text) {
    cout << "\nПолученный список частот:\n";
    for (const auto& pair : freq) {
        cout << printableChar(pair.first)
             << " (" << fixed << setprecision(3)
             << (double)pair.second / text.length() << ") ";
    }
    cout << endl;
}

// Печать дерева
void printTree(HuffmanNode* root, string indent = "") {
    if (!root) return;

    if (root->ch != '\0') {
        cout << indent << printableChar(root->ch)
             << " (" << root->freq << ")" << endl;
    } else {
        cout << indent << "* (" << root->freq << ")" << endl;
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
    printFrequencies(text);

    HuffmanNode* root = buildHuffmanTree();
    generateCodes(root, "");

    cout << "\nПостроим дерево Хаффмана...\n";
    printTree(root);

    string compressed = compress(text);

    cout << "\nПриступим к кодировке введенного текста...\n";
    cout << "Сжатый текст: " << compressed << endl;

    double ratio = compressionRatio(text, compressed);
    cout << "Коэффициент сжатия: " << fixed << setprecision(2)
         << ratio << "%" << endl;

    string decompressed = decompress(root, compressed);
    cout << "Ранее было зашифровано: " << text << endl;
    cout << "Расшифровано: " << decompressed << endl;

    return 0;
}
