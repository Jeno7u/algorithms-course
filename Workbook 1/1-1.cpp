#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
    Node *prev;
};

void show(Node *head) {
    while (head != nullptr) {
        cout << head->data << " <-> ";
        head = head->next;
    }
}

void create_node(Node *array, int n) {
    for (int i = 0; i < n; i++) {
        array[i].data = i + 1;
        if (i < n - 1) {
            array[i].next = &array[i + 1];
            array[i].prev = &array[i - 1];
        }
        else {
            array[i].next = nullptr;
        }
    }
    array[0].prev = nullptr;
}

int main() {
    const int n = 10;
    static struct Node array[n];
    struct Node *turtle, *rabbit;
    cout << "Array elements\n";
    create_node(array, n);
    show(array);

    // Создаём цикл/проскок
    array[n - 5].next = &array[3];

    // Алгоритм Флойда
    turtle = &array[0];
    rabbit = &array[1];
    while (rabbit != nullptr and rabbit->next != nullptr and turtle != rabbit) {
        turtle = turtle->next;
        rabbit = rabbit->next->next;
    }
    if (rabbit != turtle) {
        cout << "\nNo loop\n";
    }
    else {
        cout << "\nLoop detected!\n" << "Cell " << turtle->data << " references cell " << turtle->next->data <<
                "\nDone!";
    }
    return 0;
}