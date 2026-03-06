// ============================================================
// Problem: Rotate List
// Link: https://leetcode.com/problems/rotate-list/
// ============================================================
// Given the head of a linked list, rotate the list to the
// RIGHT by k places.
// Example: 1->2->3->4->5, k=2 => 4->5->1->2->3
// Example: 0->1->2, k=4 => 2->0->1
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

void freeList(ListNode *head)
{
  while (head)
  {
    ListNode *t = head;
    head = head->next;
    delete t;
  }
}

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
ListNode *rotateRight(ListNode *head, int k)
{
  // TODO: Implement this
  if (!head || !head->next || k == 0)
    return head;

  // Find length and tail
  int n = 1;
  ListNode *tail = head;
  while (tail->next)
  {
    tail = tail->next;
    n++;
  }

  k = k % n;
  if (k == 0)
    return head;

  // Make circular
  tail->next = head;

  // Find new tail at position (n - k) from head
  ListNode *newTail = head;
  for (int i = 1; i < n - k; i++)
  {
    newTail = newTail->next;
  }

  ListNode *newHead = newTail->next;
  newTail->next = nullptr;

  return newHead;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Make Circular, Then Break

    Key insight: Rotating right by k is the same as making the
    (n - k % n)th node the new tail.

    Steps:
    1. Find the length n and the tail node.
    2. k = k % n. If k == 0, no rotation needed.
    3. Connect tail->next = head (make circular).
    4. Move (n - k) steps from head to find the new tail.
    5. New head = newTail->next. Break the circle.

    Walkthrough: 1->2->3->4->5, k=2
      n = 5, tail = 5
      k = 2 % 5 = 2
      Make circular: ..5->1->2->3..
      Move (5-2)=3 steps from head(1): 1->2->3
      new_tail = 3, new_head = 4
      Break: 3->next = null
      Result: 4->5->1->2->3 ✓

    Walkthrough: 0->1->2, k=4
      n = 3, tail = 2
      k = 4 % 3 = 1
      Make circular: ..2->0->1..
      Move (3-1)=2 steps from head(0): 0->1
      new_tail = 1, new_head = 2
      Break: 1->next = null
      Result: 2->0->1 ✓

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;

        // Step 1: Find length and tail
        int n = 1;
        ListNode* tail = head;
        while (tail->next) {
            tail = tail->next;
            n++;
        }

        // Step 2: Effective rotation
        k = k % n;
        if (k == 0) return head;

        // Step 3: Make circular
        tail->next = head;

        // Step 4: Find new tail at position (n - k) from head
        ListNode* newTail = head;
        for (int i = 1; i < n - k; i++) {
            newTail = newTail->next;
        }

        // Step 5: Break the circle
        ListNode* newHead = newTail->next;
        newTail->next = nullptr;

        return newHead;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // Test 1
  int arr1[] = {1, 2, 3, 4, 5};
  ListNode *h1 = buildList(arr1, 5);
  cout << "Original: ";
  printList(h1);
  h1 = rotateRight(h1, 2);
  cout << "Rotate by 2: ";
  printList(h1);
  // Expected: 4 -> 5 -> 1 -> 2 -> 3
  freeList(h1);

  cout << endl;

  // Test 2
  int arr2[] = {0, 1, 2};
  ListNode *h2 = buildList(arr2, 3);
  cout << "Original: ";
  printList(h2);
  h2 = rotateRight(h2, 4);
  cout << "Rotate by 4: ";
  printList(h2);
  // Expected: 2 -> 0 -> 1
  freeList(h2);

  return 0;
}
