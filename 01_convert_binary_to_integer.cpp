// ============================================================
// Problem: Convert Binary Number in a Linked List to Integer
// Link: https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/
// ============================================================
// Given head of a singly linked list where each node value is 0 or 1,
// the linked list represents a binary number. Return its decimal value.
// Example: 1 -> 0 -> 1 => 5 (binary 101 = 5)
// ============================================================

#include <iostream>
using namespace std;

// -------------------- Boilerplate --------------------
struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *n) : val(x), next(n) {}
};

// Helper: Build linked list from array
ListNode *buildList(int arr[], int n)
{
  if (n == 0)
    return nullptr;
  ListNode *head = new ListNode(arr[0]);
  ListNode *curr = head;
  for (int i = 1; i < n; i++)
  {
    curr->next = new ListNode(arr[i]);
    curr = curr->next;
  }
  return head;
}

// Helper: Print linked list
void printList(ListNode *head)
{
  while (head)
  {
    cout << head->val;
    if (head->next)
      cout << " -> ";
    head = head->next;
  }
  cout << endl;
}

// Helper: Free linked list
void freeList(ListNode *head)
{
  while (head)
  {
    ListNode *tmp = head;
    head = head->next;
    delete tmp;
  }
}

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
int getDecimalValue(ListNode *head)
{
  int result = 0;
  while (head)
  {
    result = (result << 1) | head->val;
    head = head->next;
  }
  return result;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Bit Manipulation / Shift and OR

    As we traverse the linked list from head to tail, we process
    each bit from the most significant bit (MSB) to the least
    significant bit (LSB) — exactly how binary numbers are read.

    For each node:
      1. Left-shift the current result by 1 (multiply by 2)
      2. OR it with the current node's value (add the bit)

    Example: 1 -> 0 -> 1
      result = 0
      Node 1: result = (0 << 1) | 1 = 1       (binary: 1)
      Node 0: result = (1 << 1) | 0 = 2       (binary: 10)
      Node 1: result = (2 << 1) | 1 = 5       (binary: 101)

    Time Complexity:  O(n) — single pass
    Space Complexity: O(1) — no extra space

    SOLUTION CODE:
    int getDecimalValue(ListNode* head) {
        int result = 0;
        while (head) {
            result = (result << 1) | head->val;
            head = head->next;
        }
        return result;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr[] = {1, 0, 1};
  ListNode *head = buildList(arr, 3);

  cout << "List: ";
  printList(head);
  cout << "Decimal Value: " << getDecimalValue(head) << endl;
  // Expected: 5

  freeList(head);
  return 0;
}
