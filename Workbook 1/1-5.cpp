#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* next;
};

void append(Node** head, int new_data){
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head == NULL){
        *head = new_node;
        return;
    }

    Node* last = *head;
    while(last->next != NULL){
        last = last->next;
    }
    last->next = new_node;
}

void display(Node* head){
    while (head != NULL){
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << endl;
}

void reverse(Node** head){
    if (*head == NULL){
        return;
    }
    Node* prev = NULL;
    Node* curr = *head;
    Node* next = (*head)->next;

    while (next != NULL){
        curr->next = prev;

        prev = curr;
        curr = next;
        next = next->next;
    }
    curr->next = prev;

    *head = curr;
}

void summ(Node* first, Node* second, Node** result, bool reversed){
    if (!reversed){
        reverse(&first);
        reverse(&second);
    }
    Node* first_ptr = first;
    Node* second_ptr = second;

    bool plus_one = false;
    int value;
    while(first != NULL && second != NULL){
        value = (first->data + second->data) % 10;
        append(result, value + plus_one);
        plus_one = (first->data + second->data) > 9;

        first = first->next;
        second = second->next;
    }

    if (first != NULL){
        while(first != NULL){
            append(result, first->data + plus_one);
            plus_one = false;
            first = first->next;
        }
    }
    else{
        while(second != NULL){
            append(result, second->data + plus_one);
            plus_one = false;
            second = second->next;
        }
    }

    if (!reversed){
        // cout << "Before" << endl;
        // display(first_ptr);
        reverse(&first_ptr);
        reverse(&second_ptr);
        // cout << "After" << endl;
        // display(first_ptr);
        reverse(result);
    }
}

int main(){
    Node* first = NULL;
    Node* second = NULL;

    append(&first, 2);
    append(&first, 4);
    append(&first, 3);

    append(&second, 5);
    append(&second, 6);
    append(&second, 4);

    cout << "Вход при хранении в перевернутом виде (младшие разряды в начале)" << endl;
    display(first);
    display(second);


    cout << "\nВ прямом порядке (старшие разряды в начале)" << endl;
    Node* result = NULL;
    summ(first, second, &result, false);
    display(result);

    cout << "\nВ обратном порядке (младшие разряды в начале)" << endl;
    result = NULL;
    summ(first, second, &result, true);
    display(result);
}