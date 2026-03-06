// ============================================================
// Problem: Sort List (using Quick Sort)
// Link: https://leetcode.com/problems/sort-list/ (alt approach)
// ============================================================
// Sort a linked list using Quick Sort.
// (File 17 covered Merge Sort approach. This covers Quick Sort.)
// Pick the head as pivot, partition into <pivot, ==pivot, >pivot,
// recursively sort the two outer parts, and concatenate.
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
ListNode *getTail(ListNode *head)
{
  if (!head)
    return nullptr;
  while (head->next)
    head = head->next;
  return head;
}

ListNode *quickSortList(ListNode *head)
{
  // TODO: Implement this
  if (!head || !head->next)
    return head;

  int pivotVal = head->val;

  ListNode lessD(0), equalD(0), greaterD(0);
  ListNode *less = &lessD;
  ListNode *equal = &equalD;
  ListNode *greater = &greaterD;

  ListNode *curr = head;
  while (curr)
  {
    if (curr->val < pivotVal)
    {
      less->next = curr;
      less = less->next;
    }
    else if (curr->val == pivotVal)
    {
      equal->next = curr;
      equal = equal->next;
    }
    else
    {
      greater->next = curr;
      greater = greater->next;
    }
    curr = curr->next;
  }

  less->next = nullptr;
  equal->next = nullptr;
  greater->next = nullptr;

  ListNode *sortedLess = quickSortList(lessD.next);
  ListNode *sortedGreater = quickSortList(greaterD.next);

  ListNode *result;
  if (sortedLess)
  {
    result = sortedLess;
    ListNode *lessTail = getTail(sortedLess);
    lessTail->next = equalD.next;
  }
  else
  {
    result = equalD.next;
  }

  ListNode *equalTail = getTail(equalD.next);
  equalTail->next = sortedGreater;

  return result;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Quick Sort on Linked List

    1. Base case: 0 or 1 node => return.
    2. Pick HEAD as pivot.
    3. Partition: split list into 3 chains:
       - less:  nodes < pivot
       - equal: nodes == pivot
       - greater: nodes > pivot
    4. Recursively sort less and greater.
    5. Concatenate: less -> equal -> greater.

    To concatenate, find the tail of each sub-list.

    Walkthrough: 4->2->1->3

    Pivot = 4
      less: 2->1->3
      equal: 4
      greater: (empty)

    Recurse on less (2->1->3):
      Pivot = 2
      less: 1
      equal: 2
      greater: 3
      Recurse on less(1): base case => 1
      Recurse on greater(3): base case => 3
      Concat: 1 -> 2 -> 3

    Back to top:
      Concat: (1->2->3) -> (4) -> (empty) = 1->2->3->4 ✓

    Time Complexity:  O(n log n) average, O(n^2) worst case
    Space Complexity: O(log n) recursion stack

    SOLUTION CODE:
    // Helper: find tail of a list
    ListNode* getTail(ListNode* head) {
        if (!head) return nullptr;
        while (head->next) head = head->next;
        return head;
    }

    ListNode* quickSortList(ListNode* head) {
        // Base case
        if (!head || !head->next) return head;

        // Pivot is head
        int pivotVal = head->val;

        // Three dummy heads for partition
        ListNode lessD(0), equalD(0), greaterD(0);
        ListNode* less = &lessD;
        ListNode* equal = &equalD;
        ListNode* greater = &greaterD;

        ListNode* curr = head;
        while (curr) {
            if (curr->val < pivotVal) {
                less->next = curr;
                less = less->next;
            } else if (curr->val == pivotVal) {
                equal->next = curr;
                equal = equal->next;
            } else {
                greater->next = curr;
                greater = greater->next;
            }
            curr = curr->next;
        }

        // Terminate each list
        less->next = nullptr;
        equal->next = nullptr;
        greater->next = nullptr;

        // Recursively sort less and greater
        ListNode* sortedLess = quickSortList(lessD.next);
        ListNode* sortedGreater = quickSortList(greaterD.next);

        // Concatenate: sortedLess -> equalD.next -> sortedGreater
        ListNode* result;
        if (sortedLess) {
            result = sortedLess;
            ListNode* lessTail = getTail(sortedLess);
            lessTail->next = equalD.next;
        } else {
            result = equalD.next;
        }

        // equal list always has at least the pivot
        ListNode* equalTail = getTail(equalD.next);
        equalTail->next = sortedGreater;

        return result;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // Test 1
  int arr1[] = {4, 2, 1, 3};
  ListNode *h1 = buildList(arr1, 4);
  cout << "Original: ";
  printList(h1);
  h1 = quickSortList(h1);
  cout << "Sorted:   ";
  printList(h1);
  // Expected: 1 -> 2 -> 3 -> 4
  freeList(h1);

  cout << endl;

  // Test 2: With duplicates
  int arr2[] = {3, 1, 2, 3, 1};
  ListNode *h2 = buildList(arr2, 5);
  cout << "Original: ";
  printList(h2);
  h2 = quickSortList(h2);
  cout << "Sorted:   ";
  printList(h2);
  // Expected: 1 -> 1 -> 2 -> 3 -> 3
  freeList(h2);

  cout << endl;

  // Test 3: Reverse sorted
  int arr3[] = {5, 4, 3, 2, 1};
  ListNode *h3 = buildList(arr3, 5);
  cout << "Original: ";
  printList(h3);
  h3 = quickSortList(h3);
  cout << "Sorted:   ";
  printList(h3);
  // Expected: 1 -> 2 -> 3 -> 4 -> 5
  freeList(h3);

  return 0;
}
