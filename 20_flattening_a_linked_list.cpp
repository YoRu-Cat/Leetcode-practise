// ============================================================
// Problem: Flattening a Linked List
// Link: https://www.geeksforgeeks.org/problems/flattening-a-linked-list/1
// ============================================================
// Given a linked list where each node has two pointers:
//   - next: points to the next node in the main list
//   - bottom: points to a linked list of nodes (sub-list)
// Each sub-list is sorted. Flatten it into a single sorted list
// using the bottom pointer. Return the head of the flattened list.
//
// Example:
//   5 -> 10 -> 19 -> 28
//   |    |     |     |
//   7    20    22    35
//   |          |     |
//   8          50    40
//   |                |
//   30               45
//
// Result: 5->7->8->10->19->20->22->28->30->35->40->45->50
// ============================================================

#include <iostream>
using namespace std;

// -------------------- Boilerplate --------------------
struct Node
{
  int data;
  Node *next;
  Node *bottom;
  Node(int x) : data(x), next(nullptr), bottom(nullptr) {}
};

// Helper: Build the example structure
Node *buildFlattenExample()
{
  // Column 1: 5 -> 7 -> 8 -> 30
  Node *c1 = new Node(5);
  c1->bottom = new Node(7);
  c1->bottom->bottom = new Node(8);
  c1->bottom->bottom->bottom = new Node(30);

  // Column 2: 10 -> 20
  Node *c2 = new Node(10);
  c2->bottom = new Node(20);

  // Column 3: 19 -> 22 -> 50
  Node *c3 = new Node(19);
  c3->bottom = new Node(22);
  c3->bottom->bottom = new Node(50);

  // Column 4: 28 -> 35 -> 40 -> 45
  Node *c4 = new Node(28);
  c4->bottom = new Node(35);
  c4->bottom->bottom = new Node(40);
  c4->bottom->bottom->bottom = new Node(45);

  c1->next = c2;
  c2->next = c3;
  c3->next = c4;

  return c1;
}

void printFlatList(Node *head)
{
  while (head)
  {
    cout << head->data;
    if (head->bottom)
      cout << " -> ";
    head = head->bottom;
  }
  cout << endl;
}

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
Node *mergeTwoSorted(Node *a, Node *b)
{
  if (!a)
    return b;
  if (!b)
    return a;

  Node *result;
  if (a->data <= b->data)
  {
    result = a;
    result->bottom = mergeTwoSorted(a->bottom, b);
  }
  else
  {
    result = b;
    result->bottom = mergeTwoSorted(a, b->bottom);
  }
  result->next = nullptr;
  return result;
}

Node *flatten(Node *root)
{
  // TODO: Implement this
  if (!root || !root->next)
    return root;

  root->next = flatten(root->next);
  root = mergeTwoSorted(root, root->next);

  return root;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Merge from Right to Left

    Since each sub-list (bottom chain) is already sorted, this is
    essentially "merge k sorted lists" — but we can do it by merging
    two at a time from right to left.

    Start from the rightmost two sub-lists, merge them.
    Then merge the result with the next sub-list to the left.
    Continue until all are merged.

    Helper: mergeTwoSorted(a, b) — merges two sorted bottom-linked lists.

    Example:
      Step 1: Merge [28,35,40,45] and [19,22,50]
              => [19,22,28,35,40,45,50]
      Step 2: Merge [10,20] and [19,22,28,35,40,45,50]
              => [10,19,20,22,28,35,40,45,50]
      Step 3: Merge [5,7,8,30] and [10,19,20,22,28,35,40,45,50]
              => [5,7,8,10,19,20,22,28,30,35,40,45,50]

    Time Complexity:  O(n * k) where n = total nodes, k = number of sub-lists
                      Effectively O(n * number_of_merges)
    Space Complexity: O(1) — just rearranging pointers

    SOLUTION CODE:
    Node* mergeTwoSorted(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;

        Node* result;
        if (a->data <= b->data) {
            result = a;
            result->bottom = mergeTwoSorted(a->bottom, b);
        } else {
            result = b;
            result->bottom = mergeTwoSorted(a, b->bottom);
        }
        result->next = nullptr; // flatten, so no next pointer
        return result;
    }

    Node* flatten(Node* root) {
        if (!root || !root->next) return root;

        // Recursively flatten from right
        root->next = flatten(root->next);

        // Merge current list with the flattened right part
        root = mergeTwoSorted(root, root->next);

        return root;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  Node *head = buildFlattenExample();
  cout << "Flattening..." << endl;

  head = flatten(head);
  cout << "Flattened: ";
  printFlatList(head);
  // Expected: 5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 30 -> 35 -> 40 -> 45 -> 50

  return 0;
}
