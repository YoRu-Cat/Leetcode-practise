// ============================================================
// Problem: Insertion Sort List
// Link: https://leetcode.com/problems/insertion-sort-list/
// ============================================================
// Given the head of a singly linked list, sort the list using
// insertion sort, and return the sorted list's head.
//
// Insertion sort iterates, consuming one input element each
// repetition and growing a sorted output list. At each iteration,
// it removes one element from the input, finds the correct
// location in the sorted list, and inserts it there.
//
// Example: 4->2->1->3 => 1->2->3->4
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
ListNode *insertionSortList(ListNode *head)
{
  // TODO: Implement this
  ListNode dummy(0);
  dummy.next = head;

  ListNode *curr = head;
  while (curr && curr->next)
  {
    if (curr->next->val >= curr->val)
    {
      curr = curr->next;
    }
    else
    {
      ListNode *toInsert = curr->next;
      curr->next = toInsert->next;

      ListNode *prev = &dummy;
      while (prev->next->val < toInsert->val)
      {
        prev = prev->next;
      }
      toInsert->next = prev->next;
      prev->next = toInsert;
    }
  }
  return dummy.next;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Build a Sorted List Node by Node

    Maintain a "sorted" list (starting empty with a dummy head).
    For each node in the original list:
      1. Detach it from the original list
      2. Find the correct position in the sorted list
      3. Insert it there

    Use a dummy node at the start of the sorted list to simplify
    insertion at the beginning.

    Walkthrough: 4 -> 2 -> 1 -> 3

      sorted: dummy ->
      Take 4: find position => dummy -> 4
      Take 2: find position (2 < 4) => dummy -> 2 -> 4
      Take 1: find position (1 < 2) => dummy -> 1 -> 2 -> 4
      Take 3: find position (3 > 2, 3 < 4) => dummy -> 1 -> 2 -> 3 -> 4

    Optimization: if current node >= last sorted node, just append
    (no need to search from the beginning). This handles already-
    sorted or nearly-sorted inputs in O(n).

    Time Complexity:  O(n^2) worst case, O(n) best case (already sorted)
    Space Complexity: O(1) — rearranging existing nodes

    SOLUTION CODE:
    ListNode* insertionSortList(ListNode* head) {
        ListNode dummy(0);  // dummy head of sorted list
        ListNode* curr = head;

        while (curr) {
            ListNode* next = curr->next; // save next before we detach

            // Find insertion point in sorted list
            ListNode* prev = &dummy;
            while (prev->next && prev->next->val < curr->val) {
                prev = prev->next;
            }

            // Insert curr after prev
            curr->next = prev->next;
            prev->next = curr;

            curr = next; // move to next unsorted node
        }

        return dummy.next;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr[] = {4, 2, 1, 3};
  ListNode *head = buildList(arr, 4);
  cout << "Original: ";
  printList(head);

  head = insertionSortList(head);
  cout << "Sorted:   ";
  printList(head);
  // Expected: 1 -> 2 -> 3 -> 4

  freeList(head);

  int arr2[] = {-1, 5, 3, 4, 0};
  ListNode *head2 = buildList(arr2, 5);
  cout << "Original: ";
  printList(head2);
  head2 = insertionSortList(head2);
  cout << "Sorted:   ";
  printList(head2);
  // Expected: -1 -> 0 -> 3 -> 4 -> 5

  freeList(head2);
  return 0;
}
