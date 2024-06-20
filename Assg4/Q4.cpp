#include <iostream>

struct Node
{
    int data;
    Node* next;
};

void push(Node** head_ref, int new_data)
{
    Node* new_node = new Node;
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

//func to rotate list by k places
void rotate(Node** head_ref, int k)
 {
    if (k == 0 || *head_ref == nullptr) //empty list not rotated
        return;

    //get the length of the list
    int count = 1;
    Node* current = *head_ref;
    while (current->next != nullptr) {
        count++;
        current = current->next;
    }

    //handle the case where k might be greater than list length
    k = k % count;

    //find the kth node from the end (new tail)
    current = *head_ref;
    for (int i = 1; i <= count - k -1; i++) {
        current = current->next;
    }

    //set the new tail's next to the head (making the list circular)
    Node* new_tail = current;
    current = current->next;
    new_tail->next = nullptr;
    *head_ref = current;
}

//to print the linked list
void printList(Node* node)
{
    while (node != nullptr) {
        std::cout << node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

int main()
{
    Node* head = nullptr;
    push(&head, 5);
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    std::cout << "Given linked list: ";
    printList(head);

    int k = 2;
    rotate(&head, k);

    std::cout << "Rotated linked list by " << k << " places: ";
    printList(head);

    return 0;
}
