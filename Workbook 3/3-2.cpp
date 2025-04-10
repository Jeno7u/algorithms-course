#include <iostream>
#include <vector>
using namespace std;

class BinaryHeap {
private:
    vector<int> heap;

public:
    BinaryHeap(): heap({}) {}

    BinaryHeap(initializer_list<int> heap){
        this->heap = heap;
        convertToMaxHeap(this->heap); 
    }

    void printHeap() {
        for (int val : heap)
            cout << val << " ";
        cout << endl;
    }

    void heapify(vector<int>& arr, int n, int i) {
        int largest = i;        
        int left = 2 * i + 1;   
        int right = 2 * i + 2;  
    
        if (left < n && arr[left] > arr[largest])
            largest = left;
    
        if (right < n && arr[right] > arr[largest])
            largest = right;
    
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
    
    void convertToMaxHeap(vector<int>& arr) {
        int n = arr.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
    }

    int getMax(){
        return heap[0];
    }
    
    void insert(int value){
        heap.push_back(value);
        int index = heap.size() - 1;
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

    void deleteMax(){
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();

        int index = 0;
        while(index < heap.size() - 1){
            int left = index * 2 + 1;
            int right = index * 2 + 2;

            if ((left < heap.size() && heap[index] > heap[left]) && (right < heap.size() && heap[index] > heap[right])){
                break;
            }
            else if (left < heap.size() && heap[left] > heap[index]){
                swap(heap[index], heap[left]);
                index = left;
            }
            else if (right < heap.size() && heap[right] > heap[index]){
                swap(heap[index], heap[right]);
                index = right;
            }
            else{
                break;
            }
        }
    }
};

int main() {
    BinaryHeap heap = {10, 20, 5, 40, 15};
    heap.printHeap();
    cout << "Max: " << heap.getMax() << endl;

    cout << "\nDeletiong of max..." << endl;
    heap.deleteMax();
    heap.printHeap();

    cout << "\nAdding elemnt 16..." << endl;
    heap.insert(16);
    heap.printHeap(); 
    return 0;
}