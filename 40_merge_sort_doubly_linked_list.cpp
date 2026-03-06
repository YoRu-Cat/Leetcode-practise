// ============================================================
// Problem: Merge Sort on Doubly Linked List
// Link: https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/
// ============================================================
// Sort a doubly linked list using Merge Sort.
// This extends the singly-linked merge sort to handle prev ptrs.
// Example: 5<->3<->4<->1<->2 => 1<->2<->3<->4<->5
// ============================================================

#include <iostream>
using namespace std;

// -------------------- Boilerplate --------------------
struct DListNode
{
  int val;
  DListNode *prev;
  DListNode *next;
  DListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
};

DListNode *buildDList(int arr[], int n)
{
  if (n == 0)
    return nullptr;
  DListNode *head = new DListNode(arr[0]);
  DListNode *curr = head;
  for (int i = 1; i < n; i++)
  {
    DListNode *node = new DListNode(arr[i]);
    curr->next = node;
    node->prev = curr;
    curr = node;
  }
  return head;
}

void printDList(DListNode *head)
{
  while (head)
  {
    cout << head->val;
    if (head->next)
      cout << " <-> ";
    head = head->next;
  }
  cout << endl;
}

void printDListReverse(DListNode *head)
{
  if (!head)
    return;
  DListNode *tail = head;
  while (tail->next)
    tail = tail->next;
  while (tail)
  {
    cout << tail->val;
    if (tail->prev)
      cout << " <-> ";
    tail = tail->prev;
  }
  cout << endl;
}

void freeDList(DListNode *head)
{
  while (head)
  {
    DListNode *t = head;
    head = head->next;
    delete t;
  }
}

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
DListNode *mergeTwoSortedDLL(DListNode *a, DListNode *b)
{
  if (!a)
    return b;
  if (!b)
    return a;

  DListNode dummy(0);
  DListNode *tail = &dummy;

  while (a && b)
  {
    if (a->val <= b->val)
    {
      tail->next = a;
      a->prev = tail;
      a = a->next;
    }
    else
    {
      tail->next = b;
      b->prev = tail;
      b = b->next;
    }
    tail = tail->next;
  }

  if (a)
  {
    tail->next = a;
    a->prev = tail;
  }
  if (b)
  {
    tail->next = b;
    b->prev = tail;
  }

  DListNode *head = dummy.next;
  head->prev = nullptr;
  return head;
}

DListNode *mergeSortDLL(DListNode *head)
{
  // TODO: Implement this
  if (!head || !head->next)
    return head;

  // Find middle
  DListNode *slow = head;
  DListNode *fast = head;
  while (fast->next && fast->next->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }

  // Split
  DListNode *second = slow->next;
  slow->next = nullptr;
  second->prev = nullptr;

  // Sort each half
  DListNode *left = mergeSortDLL(head);
  DListNode *right = mergeSortDLL(second);

  // Merge
  return mergeTwoSortedDLL(left, right);
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Merge Sort (adapted for doubly linked list)

    Same idea as singly-linked merge sort:
    1. Find the middle using slow/fast pointers.
    2. Split into two halves.
    3. Recursively sort each half.
    4. Merge the two sorted halves.

    The only extra step is maintaining the prev pointers when merging.

    Split helper:
      Use slow/fast to find middle.
      second = slow->next
      slow->next = nullptr
      second->prev = nullptr

    Merge helper:
      Standard merge of two sorted lists.
      When attaching a node, also set node->prev = tail.

    Walkthrough: 5 <-> 3 <-> 4 <-> 1 <-> 2

    Split: [5,3,4] and [1,2]
    Recurse [5,3,4]:
      Split: [5,3] and [4]
      Recurse [5,3]:
        Split: [5] and [3]
        Merge: 3 <-> 5
      Merge [3,5] with [4]: 3 <-> 4 <-> 5
    Recurse [1,2]:
      Split: [1] and [2]
      Merge: 1 <-> 2
    Merge [3,4,5] with [1,2]:
      1 < 3 => 1
      2 < 3 => 1 <-> 2
      3 => 1 <-> 2 <-> 3
      4 => 1 <-> 2 <-> 3 <-> 4
      5 => 1 <-> 2 <-> 3 <-> 4 <-> 5 ✓

    Time Complexity:  O(n log n)
    Space Complexity: O(log n) recursion stack

    SOLUTION CODE:
    DListNode* mergeTwoSortedDLL(DListNode* a, DListNode* b) {
        if (!a) return b;
        if (!b) return a;

        DListNode dummy(0);
        DListNode* tail = &dummy;

        while (a && b) {
            if (a->val <= b->val) {
                tail->next = a;
                a->prev = tail;
                a = a->next;
            } else {
                tail->next = b;
                b->prev = tail;
                b = b->next;
            }
            tail = tail->next;
        }

        if (a) { tail->next = a; a->prev = tail; }
        if (b) { tail->next = b; b->prev = tail; }

        DListNode* head = dummy.next;
        head->prev = nullptr;  // head has no previous
        return head;
    }

    DListNode* mergeSortDLL(DListNode* head) {
        if (!head || !head->next) return head;

        // Find middle
        DListNode* slow = head;
        DListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Split
        DListNode* second = slow->next;
        slow->next = nullptr;
        second->prev = nullptr;

        // Sort each half
        DListNode* left = mergeSortDLL(head);
        DListNode* right = mergeSortDLL(second);

        // Merge
        return mergeTwoSortedDLL(left, right);
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // Test 1
  int arr1[] = {5, 3, 4, 1, 2};
  DListNode *h1 = buildDList(arr1, 5);
  cout << "Original (fwd):  ";
  printDList(h1);
  h1 = mergeSortDLL(h1);
  cout << "Sorted (fwd):    ";
  printDList(h1);
  cout << "Sorted (rev):    ";
  printDListReverse(h1);
  // Expected fwd: 1 <-> 2 <-> 3 <-> 4 <-> 5
  // Expected rev: 5 <-> 4 <-> 3 <-> 2 <-> 1
  freeDList(h1);

  cout << endl;

  // Test 2
  int arr2[] = {10, -1, 7, 3, 0};
  DListNode *h2 = buildDList(arr2, 5);
  cout << "Original (fwd):  ";
  printDList(h2);
  h2 = mergeSortDLL(h2);
  cout << "Sorted (fwd):    ";
  printDList(h2);
  cout << "Sorted (rev):    ";
  printDListReverse(h2);
  // Expected fwd: -1 <-> 0 <-> 3 <-> 7 <-> 10
  freeDList(h2);

  return 0;
}
