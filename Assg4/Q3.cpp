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

//finding the middle of the linked list using slow and fast pointer
//slow pointer moves one node at a time
//fast point moves two nodes at a time
//when the fast pointer reaches the end of the linked list, the slow pointer is at the middle
Node* getMiddle(Node* head)
{
  Node* slow = head;
  Node* fast = head;

  while (fast != nullptr && fast->next != nullptr)
  {
    slow = slow->next;
    fast = fast->next->next;
  }
  // For odd number of nodes, slow points to the middle node
  // For even number of nodes, slow points to the second node of the second half
  return slow;
}

// Function to reverse a linked list (iterative)
void reverse(Node** head_ref)
{
  Node* prev = nullptr;
  Node* current = *head_ref;
  Node* next;

  while (current != nullptr)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  (*head_ref) = prev;
}

// Function to check if a linked list is a palindrome
bool isPalindrome(Node* head)
{
  // Find the middle node
  Node* middle = getMiddle(head);

  // Reverse the second half of the linked list
  reverse(&middle);

  // One pointer at the beginning and one at the modified middle
  Node* left = head;
  Node* right = middle;

  // Compare elements until they meet or right becomes null
  while (right != nullptr)
  {
    if (left->data != right->data)
      return false;
    left = left->next;
    right = right->next;
  }

  // If loop completes, all elements matched, so it's a palindrome
  return true;
}

// Function to print the linked list
void printList(Node* node)
{
  while (node != nullptr)
  {
    std::cout << node->data << " ";
    node = node->next;
  }
  std::cout << std::endl;
}

int main() {
  Node* head = nullptr;
  push(&head, 1);
  push(&head, 2);
  push(&head, 2);
  push(&head, 1);

  std::cout << "Given linked list: ";
  printList(head);

  bool result = isPalindrome(head);

  (result) ? std::cout << "List is a palindrome"
           : std::cout << "List is not a palindrome";
  std::cout << std::endl;

  return 0;
}
