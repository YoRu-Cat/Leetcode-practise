// ============================================================
// Problem: Reorder List
// Link: https://leetcode.com/problems/reorder-list/
// ============================================================
// Given head of a singly linked list:
//   L0 -> L1 -> L2 -> ... -> Ln-1 -> Ln
// Reorder it to:
//   L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 -> ...
// You may NOT modify node values, only rearrange nodes.
// Example: 1->2->3->4 => 1->4->2->3
// Example: 1->2->3->4->5 => 1->5->2->4->3
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
void reorderList(ListNode *head)
{
  // TODO: Implement this
  if (!head || !head->next)
    return;

  // Step 1: Find middle
  ListNode *slow = head;
  ListNode *fast = head;
  while (fast->next && fast->next->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }

  // Step 2: Reverse second half
  ListNode *prev = nullptr;
  ListNode *curr = slow->next;
  slow->next = nullptr;
  while (curr)
  {
    ListNode *nxt = curr->next;
    curr->next = prev;
    prev = curr;
    curr = nxt;
  }

  // Step 3: Merge two halves alternately
  ListNode *first = head;
  ListNode *second = prev;
  while (second)
  {
    ListNode *tmp1 = first->next;
    ListNode *tmp2 = second->next;
    first->next = second;
    second->next = tmp1;
    first = tmp1;
    second = tmp2;
  }
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: 3 Steps — Find Middle + Reverse + Merge

    Step 1: Find the middle of the list (slow/fast pointer).
    Step 2: Reverse the second half.
    Step 3: Merge (interleave) the two halves.

    This combines THREE fundamental linked list techniques:
      - Finding middle (used in merge sort of list)
      - Reversing a list
      - Merging two lists alternately

    Walkthrough: 1->2->3->4->5

    Step 1: Find middle
      slow=1,fast=1 -> slow=2,fast=3 -> slow=3,fast=5
      Middle = 3. Split: first = 1->2->3, second = 4->5

    Step 2: Reverse second half
      4->5 becomes 5->4

    Step 3: Merge alternately
      Take from first:  1 ->
      Take from second: 5 ->
      Take from first:  2 ->
      Take from second: 4 ->
      Take from first:  3
      Result: 1->5->2->4->3 ✓

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        // Step 1: Find middle
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Reverse second half
        ListNode* prev = nullptr;
        ListNode* curr = slow->next;
        slow->next = nullptr;     // cut the list in half
        while (curr) {
            ListNode* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        // prev is the head of the reversed second half

        // Step 3: Merge two halves alternately
        ListNode* first = head;
        ListNode* second = prev;
        while (second) {
            ListNode* tmp1 = first->next;
            ListNode* tmp2 = second->next;
            first->next = second;
            second->next = tmp1;
            first = tmp1;
            second = tmp2;
        }
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // Test 1: Even length
  int arr1[] = {1, 2, 3, 4};
  ListNode *h1 = buildList(arr1, 4);
  cout << "Original: ";
  printList(h1);
  reorderList(h1);
  cout << "Reordered: ";
  printList(h1);
  // Expected: 1 -> 4 -> 2 -> 3
  freeList(h1);

  cout << endl;

  // Test 2: Odd length
  int arr2[] = {1, 2, 3, 4, 5};
  ListNode *h2 = buildList(arr2, 5);
  cout << "Original: ";
  printList(h2);
  reorderList(h2);
  cout << "Reordered: ";
  printList(h2);
  // Expected: 1 -> 5 -> 2 -> 4 -> 3
  freeList(h2);

  return 0;
}
