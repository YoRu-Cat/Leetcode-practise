// ============================================================
// Problem: Sort List
// Link: https://leetcode.com/problems/sort-list/
// ============================================================
// Given the head of a linked list, return the list after sorting
// it in ascending order. Must be O(n log n) time and O(1) space
// (ignoring recursion stack).
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
ListNode *merge(ListNode *l1, ListNode *l2)
{
  ListNode dummy;
  ListNode *tail = &dummy;
  while (l1 && l2)
  {
    if (l1->val <= l2->val)
    {
      tail->next = l1;
      l1 = l1->next;
    }
    else
    {
      tail->next = l2;
      l2 = l2->next;
    }
    tail = tail->next;
  }
  tail->next = l1 ? l1 : l2;
  return dummy.next;
}

ListNode *sortList(ListNode *head)
{
  // TODO: Implement this
  if (!head || !head->next)
    return head;

  ListNode *slow = head;
  ListNode *fast = head->next;
  while (fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode *mid = slow->next;
  slow->next = nullptr;

  ListNode *left = sortList(head);
  ListNode *right = sortList(mid);

  return merge(left, right);
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Merge Sort on Linked List

    Linked lists are perfect for merge sort because merging two sorted
    lists is O(1) extra space (just rearrange pointers).

    Steps:
      1. Find the middle of the list (slow/fast pointer)
      2. Split the list into two halves
      3. Recursively sort each half
      4. Merge the two sorted halves

    Base case: empty list or single node (already sorted).

    Example: 4 -> 2 -> 1 -> 3
      Split: [4, 2] and [1, 3]
      Sort [4, 2]:
        Split: [4] and [2]
        Merge: 2 -> 4
      Sort [1, 3]:
        Split: [1] and [3]
        Merge: 1 -> 3
      Merge [2->4] and [1->3]:
        Compare 2 vs 1 => 1
        Compare 2 vs 3 => 2
        Compare 4 vs 3 => 3
        Remaining: 4
        Result: 1 -> 2 -> 3 -> 4

    Time Complexity:  O(n log n)
    Space Complexity: O(log n) recursion stack

    SOLUTION CODE:
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }

    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        // Find middle
        ListNode* slow = head;
        ListNode* fast = head->next; // important: use head->next so slow stops before mid
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Split
        ListNode* mid = slow->next;
        slow->next = nullptr;

        // Recursively sort both halves
        ListNode* left = sortList(head);
        ListNode* right = sortList(mid);

        // Merge
        return merge(left, right);
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr[] = {4, 2, 1, 3};
  ListNode *head = buildList(arr, 4);
  cout << "Original: ";
  printList(head);

  head = sortList(head);
  cout << "Sorted:   ";
  printList(head);
  // Expected: 1 -> 2 -> 3 -> 4

  freeList(head);
  return 0;
}
