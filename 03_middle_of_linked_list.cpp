// ============================================================
// Problem: Middle of the Linked List
// Link: https://leetcode.com/problems/middle-of-the-linked-list/
// ============================================================
// Given the head of a singly linked list, return the middle node.
// If there are two middle nodes, return the second middle node.
// Example: 1->2->3->4->5 => return node 3
//          1->2->3->4->5->6 => return node 4 (second middle)
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
ListNode *middleNode(ListNode *head)
{
  ListNode *slow = head;
  ListNode *fast = head;
  while (fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Slow and Fast Pointer (Tortoise & Hare)

    Use two pointers:
      - slow moves 1 step at a time
      - fast moves 2 steps at a time

    When fast reaches the end, slow is at the middle.

    Why? fast travels 2x the speed of slow. When fast has covered
    the full length, slow has covered half.

    For even-length lists, fast will become null (not fast->next),
    and slow will be at the second middle — exactly what we want.

    Example (odd):  1 -> 2 -> 3 -> 4 -> 5
      slow: 1, 2, 3         fast: 1, 3, 5
      fast->next is null => slow at 3 ✓

    Example (even): 1 -> 2 -> 3 -> 4 -> 5 -> 6
      slow: 1, 2, 3, 4      fast: 1, 3, 5, null
      fast is null => slow at 4 ✓

    Time Complexity:  O(n) — single pass
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr1[] = {1, 2, 3, 4, 5};
  ListNode *head1 = buildList(arr1, 5);
  cout << "List: ";
  printList(head1);
  ListNode *mid1 = middleNode(head1);
  cout << "Middle: " << (mid1 ? mid1->val : -1) << endl; // Expected: 3

  int arr2[] = {1, 2, 3, 4, 5, 6};
  ListNode *head2 = buildList(arr2, 6);
  cout << "List: ";
  printList(head2);
  ListNode *mid2 = middleNode(head2);
  cout << "Middle: " << (mid2 ? mid2->val : -1) << endl; // Expected: 4

  freeList(head1);
  freeList(head2);
  return 0;
}
