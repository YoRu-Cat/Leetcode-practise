// ============================================================
// Problem: Merge Two Sorted Lists
// Link: https://leetcode.com/problems/merge-two-sorted-lists/
// ============================================================
// Merge two sorted linked lists and return it as a new sorted list.
// Example: 1->2->4  and  1->3->4  =>  1->1->2->3->4->4
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
ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
  // TODO: Implement this
  ListNode dummy;
  ListNode *tail = &dummy;

  while (list1 && list2)
  {
    if (list1->val <= list2->val)
    {
      tail->next = list1;
      list1 = list1->next;
    }
    else
    {
      tail->next = list2;
      list2 = list2->next;
    }
    tail = tail->next;
  }
  tail->next = list1 ? list1 : list2;
  return dummy.next;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Iterative Merge with Dummy Node

    Use a dummy node as the start of the result list.
    Compare the heads of both lists, pick the smaller one,
    attach it to the result, and advance that list's pointer.
    When one list is exhausted, attach the remaining of the other.

    Walkthrough: l1 = 1->2->4,  l2 = 1->3->4
      dummy -> ?
      Compare 1 vs 1: pick l1(1), dummy->1
      Compare 2 vs 1: pick l2(1), 1->1
      Compare 2 vs 3: pick l1(2), 1->2
      Compare 4 vs 3: pick l2(3), 2->3
      Compare 4 vs 4: pick l1(4), 3->4
      l1 exhausted, attach l2(4): 4->4
      Result: 1->1->2->3->4->4

    Time Complexity:  O(m + n)
    Space Complexity: O(1)

    SOLUTION CODE (Iterative):
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy;
        ListNode* tail = &dummy;

        while (list1 && list2) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        tail->next = list1 ? list1 : list2;
        return dummy.next;
    }

    SOLUTION CODE (Recursive):
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        if (l1->val <= l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int a1[] = {1, 2, 4};
  int a2[] = {1, 3, 4};
  ListNode *l1 = buildList(a1, 3);
  ListNode *l2 = buildList(a2, 3);

  cout << "List 1: ";
  printList(l1);
  cout << "List 2: ";
  printList(l2);

  ListNode *merged = mergeTwoLists(l1, l2);
  cout << "Merged: ";
  printList(merged);
  // Expected: 1 -> 1 -> 2 -> 3 -> 4 -> 4

  freeList(merged);
  return 0;
}
