// ============================================================
// Problem: Partition List
// Link: https://leetcode.com/problems/partition-list/
// ============================================================
// Given the head of a linked list and a value x, partition it
// such that all nodes LESS THAN x come before nodes >= x.
// Preserve the original relative order within each partition.
// Example: 1->4->3->2->5->2, x=3 => 1->2->2->4->3->5
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
ListNode *partition(ListNode *head, int x)
{
  // TODO: Implement this
  ListNode beforeDummy(0), afterDummy(0);
  ListNode *before = &beforeDummy;
  ListNode *after = &afterDummy;

  while (head)
  {
    if (head->val < x)
    {
      before->next = head;
      before = before->next;
    }
    else
    {
      after->next = head;
      after = after->next;
    }
    head = head->next;
  }

  after->next = nullptr;
  before->next = afterDummy.next;
  return beforeDummy.next;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Two Dummy Lists (Before and After)

    Create two separate lists:
      - "before": nodes with val < x
      - "after":  nodes with val >= x

    Traverse original list, append each node to the correct list.
    Then connect before's tail to after's head.

    This is similar to the Sort 0s/1s/2s problem but with 2 partitions.

    Walkthrough: 1->4->3->2->5->2, x=3
      before_dummy -> ?
      after_dummy  -> ?

      Node 1: 1 < 3 => before: 1
      Node 4: 4 >= 3 => after: 4
      Node 3: 3 >= 3 => after: 4->3
      Node 2: 2 < 3 => before: 1->2
      Node 5: 5 >= 3 => after: 4->3->5
      Node 2: 2 < 3 => before: 1->2->2

      Connect: before_tail->next = after_head
               after_tail->next = null
      Result: 1->2->2->4->3->5 ✓

    Note: relative order within each group is preserved!

    Time Complexity:  O(n)
    Space Complexity: O(1) — just rearranging pointers

    SOLUTION CODE:
    ListNode* partition(ListNode* head, int x) {
        ListNode beforeDummy(0), afterDummy(0);
        ListNode* before = &beforeDummy;
        ListNode* after = &afterDummy;

        while (head) {
            if (head->val < x) {
                before->next = head;
                before = before->next;
            } else {
                after->next = head;
                after = after->next;
            }
            head = head->next;
        }

        after->next = nullptr;            // terminate the after list
        before->next = afterDummy.next;    // connect before -> after
        return beforeDummy.next;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr[] = {1, 4, 3, 2, 5, 2};
  ListNode *head = buildList(arr, 6);
  cout << "Original: ";
  printList(head);

  head = partition(head, 3);
  cout << "Partition (x=3): ";
  printList(head);
  // Expected: 1 -> 2 -> 2 -> 4 -> 3 -> 5

  freeList(head);
  return 0;
}
