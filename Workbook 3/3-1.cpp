#include <iostream>
#include <vector>
using namespace std;

vector<int> heap;

void heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] > heap[parent]) {
            swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

// Вставка элемента в кучу
void insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

// Вывод кучи
void printHeap() {
    for (int val : heap)
        cout << val << " ";
    cout << endl;
}

int main() {
    insert(10);
    insert(20);
    insert(5);
    insert(30);
    insert(2);
    cout << "Куча после вставки элементов: ";
    printHeap();
    return 0;
}