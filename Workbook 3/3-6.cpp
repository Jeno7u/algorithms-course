#include <iostream>
using namespace std;

struct Node {
    int value;
    int priority;
    Node* next;
};

Node* createNode(int value, int priority) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->priority = priority;
    newNode->next = nullptr;
    return newNode;
}

void push(Node** head, int value, int priority) {
    Node* newNode = createNode(value, priority);
    
    if (*head == nullptr || priority > (*head)->priority) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        
        while (current->next != nullptr && current->next->priority >= priority) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
    }
}

int getMax(Node** head) {
    if (*head == nullptr) {
        cout << "Очередь пуста!" << endl;
        return -1; 
    }
    
    Node* temp = *head;
    int value = temp->value;
    *head = (*head)->next;
    delete temp;
    return value;
}

int getMin(Node** head) {
    if (*head == nullptr) {
        cout << "Очередь пуста!" << endl;
        return -1;
    }

    if ((*head)->next == nullptr) {
        int value = (*head)->value;
        delete *head;
        *head = nullptr;
        return value;
    }
    
    Node* prev = nullptr;
    Node* current = *head;
    while (current->next != nullptr) {
        prev = current;
        current = current->next;
    }
    
    int value = current->value;
    prev->next = nullptr;
    delete current;
    return value;
}

void freeQueue(Node** head) {
    while (*head != nullptr) {
        Node* temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}

void printQueue(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << "(" << current->value << ", " << current->priority << ") ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    Node* queue = nullptr;
    
    push(&queue, 10, 2);
    push(&queue, 20, 1);
    push(&queue, 30, 3);
    push(&queue, 40, 0);
    
    cout << "Очередь: ";
    printQueue(queue);
    
    cout << "Извлекаем максимум: " << getMax(&queue) << endl;
    cout << "Извлекаем минимум: " << getMin(&queue) << endl;
    cout << "Извлекаем максимум: " << getMax(&queue) << endl;
    
    cout << "Очередь после извлечения: ";
    printQueue(queue);
    
    freeQueue(&queue);
    
    return 0;
}