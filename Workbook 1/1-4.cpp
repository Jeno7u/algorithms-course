#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* prev;
    Node* next;
};


void append(Node** head, int new_data){
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head == NULL){
        new_node->prev = nullptr;
        *head = new_node;
        return;
    }

    if ((*head)->prev != NULL){
        new_node->prev = (*head)->prev;
        new_node->next = *head;

        (*head)->prev->next = new_node;
        (*head)->prev = new_node;
    }
    else{
        Node* last = *head;
        while(last->next != NULL){
            last = last->next;
        }
        new_node->prev = last;
        last->next = new_node;
    }
}

void append_before(Node** head, int value, int new_data){
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = NULL;

    Node* last = *head;
    while(last->data != value){
        last = last->next;
    }
    new_node->prev = last->next;
    new_node->next = last;

    last->prev->next = new_node;
    last->prev = new_node;
}

void display_cycle(Node* head, bool reverse = false){
    if (head == NULL){
        cout << " -> NULL -> " << endl;
        return;
    }

    Node* head_ptr = head;
    if (!reverse){
        cout << " -> " << head->data;
        head = head->next;
        while (head != head_ptr){
            cout << " -> " << head->data;
            head = head->next;
        }
        cout << " -> " << endl;
    }
    else{
        cout << " <- " << head->data;
        head = head->prev;
        while (head != head_ptr){
            cout << " <- " << head->data;
            head = head->prev;
        }
        cout << " <- " << endl;
    }
}

void close_cycle(Node* head){
    Node* last = head;
    while(last->next != NULL){
        last = last->next;
    }
    head->prev = last;
    last->next = head;
}

void remove(Node** head, int value){
    Node* head_ptr = *head;
    if (head_ptr->data == value){
        head_ptr->prev->next = head_ptr->next;
        delete head_ptr;
        *head = head_ptr->next;
        return;
    }

    while (head_ptr->data != value){
        head_ptr = head_ptr->next;
    }
    head_ptr->prev->next = head_ptr->next;
}

int count_list(Node* head){
    if (head == NULL){
        return 0;
    }

    int count = 1;
    Node* head_ptr = head;
    head = head->next;
    while (head != head_ptr){
        count++;
        head = head->next;
    }
    return count;
}


int main(){
    // создание двусвязного списка
    Node* head = NULL;
    append(&head, -8);
    append(&head, 4);
    append(&head, 1);
    append(&head, 9);

    // замыкание списка на самого себя
    close_cycle(head);

    cout << "Двусвязный кольцевой список в прямом и обратном порядке" << endl;
    display_cycle(head);
    display_cycle(head, true);

    cout << "\nДобавляем элементы со значением 3 и 8 в конец списка" << endl;
    append(&head, 3);
    append(&head, 8);
    display_cycle(head);

    cout << "\nСоздаем элемент со значением 10 перед элементом со значением 1" << endl;
    append_before(&head, 1, 10);
    display_cycle(head);

    cout << "\nУдаление узла со занчением 9" << endl;
    remove(&head, 9);
    display_cycle(head);

    cout << "\nКол-во элементов в списке: " << count_list(head) << endl;
}