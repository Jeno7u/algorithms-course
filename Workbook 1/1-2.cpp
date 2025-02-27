#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
};

tuple<Node*, Node*> convert(Node* head, int x) {
    Node* head1 = NULL, *head2 = NULL;
    Node* last1 = NULL, *last2 = NULL;

    while (head != NULL) {
        Node* nextNode = head->next;
        
        if (head->data < x) {
            if (head1 == NULL) {
                head1 = head;
                last1 = head;
            } else {
                last1->next = head;
                last1 = head;
            }
        } else {
            if (head2 == NULL) {
                head2 = head;
                last2 = head;
            } else {
                last2->next = head;
                last2 = head;
            }
        }
        
        head->next = NULL;
        head = nextNode;
    }

    return {head1, head2};
}

void printList(Node* head) {
    while (head) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

void append(Node** head, int new_data) {
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

int main() {
    Node* head = NULL;

    append(&head, 1);
    append(&head, 4);
    append(&head, 3);
    append(&head, 2);
    append(&head, 5);
    append(&head, 2);

    cout << "Original List: ";
    printList(head);

    auto [head1, head2] = convert(head, 3);

    cout << "List with elements < 3: ";
    printList(head1);

    cout << "List with elements >= 3: ";
    printList(head2);
}
