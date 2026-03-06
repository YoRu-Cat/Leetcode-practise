// ============================================================
// Problem: Sort Linked List Already Sorted on Absolute Values
// Link: https://www.geeksforgeeks.org/sort-linked-list-already-sorted-on-absolute-values/
// ============================================================
// Given a linked list that is sorted based on ABSOLUTE values,
// sort it based on actual values.
// Example: 1->-2->-3->4->-5
//   Abs sorted: |1|=1, |-2|=2, |-3|=3, |4|=4, |-5|=5 ✓
//   Actual sort: -5->-3->-2->1->4
// ============================================================

#include <iostream>
#include <cstdlib> // for abs()
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
ListNode *sortByActualValues(ListNode *head)
{
  // TODO: Implement this
  if (!head || !head->next)
    return head;

  ListNode *prev = head;
  ListNode *curr = head->next;

  while (curr)
  {
    if (curr->val < 0)
    {
      prev->next = curr->next;
      curr->next = head;
      head = curr;
      curr = prev->next;
    }
    else
    {
      prev = curr;
      curr = curr->next;
    }
  }

  return head;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Move negatives to front

    Since the list is sorted by absolute values, all positive numbers
    are ALREADY in correct relative order. Negative numbers just need
    to be moved to the front (in reverse order of their appearance).

    Traverse the list. If a node is negative, detach it and insert
    it at the head. This reverses the order of negatives, but since
    the original list has negatives in increasing absolute value,
    reversing them puts them in decreasing order (which is the
    correct sorted order for negatives).

    Walkthrough: 1 -> -2 -> -3 -> 4 -> -5

    prev=1, curr=-2: negative, move to front
      head = -2 -> 1 -> -3 -> 4 -> -5
      prev=1, curr=-3

    prev=1, curr=-3: negative, move to front
      head = -3 -> -2 -> 1 -> 4 -> -5
      prev=1, curr=4

    prev=1, curr=4: positive, just advance
      prev=4, curr=-5

    prev=4, curr=-5: negative, move to front
      head = -5 -> -3 -> -2 -> 1 -> 4
      prev=4, curr=null => done

    Result: -5 -> -3 -> -2 -> 1 -> 4 ✓

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* sortByActualValues(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* prev = head;
        ListNode* curr = head->next;

        while (curr) {
            if (curr->val < 0) {
                // Detach curr
                prev->next = curr->next;
                // Insert at head
                curr->next = head;
                head = curr;
                // Move to next (prev stays the same)
                curr = prev->next;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        return head;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // Test 1
  int arr1[] = {1, -2, -3, 4, -5};
  ListNode *h1 = buildList(arr1, 5);
  cout << "Abs-sorted: ";
  printList(h1);
  h1 = sortByActualValues(h1);
  cout << "Actual sort: ";
  printList(h1);
  // Expected: -5 -> -3 -> -2 -> 1 -> 4
  freeList(h1);

  cout << endl;

  // Test 2
  int arr2[] = {0, -1, 2, -3};
  ListNode *h2 = buildList(arr2, 4);
  cout << "Abs-sorted: ";
  printList(h2);
  h2 = sortByActualValues(h2);
  cout << "Actual sort: ";
  printList(h2);
  // Expected: -3 -> -1 -> 0 -> 2
  freeList(h2);

  cout << endl;

  // Test 3: All positive (already sorted)
  int arr3[] = {1, 2, 3};
  ListNode *h3 = buildList(arr3, 3);
  cout << "Abs-sorted: ";
  printList(h3);
  h3 = sortByActualValues(h3);
  cout << "Actual sort: ";
  printList(h3);
  // Expected: 1 -> 2 -> 3
  freeList(h3);

  return 0;
}
