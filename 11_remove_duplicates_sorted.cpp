// ============================================================
// Problem: Remove Duplicates from Sorted List
// Link: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
// ============================================================
// Given the head of a sorted linked list, delete all duplicates
// such that each element appears only once. Return the sorted list.
// Example: 1->1->2->3->3 => 1->2->3
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
ListNode *deleteDuplicates(ListNode *head)
{
  ListNode *curr = head;
  while (curr && curr->next)
  {
    if (curr->val == curr->next->val)
    {
      ListNode *dup = curr->next;
      curr->next = curr->next->next;
      delete dup; // free memory
    }
    else
    {
      curr = curr->next;
    }
  }
  return head;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Single Pass — Skip Duplicates

    Since the list is SORTED, all duplicates are adjacent.
    Traverse the list: if current node's value == next node's value,
    skip the next node by pointing curr->next to curr->next->next.
    Otherwise, move curr forward.

    Walkthrough: 1 -> 1 -> 2 -> 3 -> 3
      curr = 1: curr->val(1) == curr->next->val(1) => skip
                1 -> 2 -> 3 -> 3
      curr = 1: curr->val(1) != curr->next->val(2) => advance
      curr = 2: curr->val(2) != curr->next->val(3) => advance
      curr = 3: curr->val(3) == curr->next->val(3) => skip
                1 -> 2 -> 3
      curr = 3: curr->next is null => done

    Result: 1 -> 2 -> 3

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* curr = head;
        while (curr && curr->next) {
            if (curr->val == curr->next->val) {
                ListNode* dup = curr->next;
                curr->next = curr->next->next;
                delete dup; // free memory
            } else {
                curr = curr->next;
            }
        }
        return head;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr[] = {1, 1, 2, 3, 3};
  ListNode *head = buildList(arr, 5);
  cout << "Original: ";
  printList(head);

  head = deleteDuplicates(head);
  cout << "Deduped:  ";
  printList(head);
  // Expected: 1 -> 2 -> 3

  freeList(head);
  return 0;
}
