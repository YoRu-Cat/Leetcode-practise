// ============================================================
// Problem: Remove Nth Node From End of List
// Link: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
// ============================================================
// Given the head of a linked list, remove the nth node from
// the end of the list and return its head.
// Example: 1->2->3->4->5, n=2 => 1->2->3->5 (removed 4)
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
ListNode *removeNthFromEnd(ListNode *head, int n)
{
  // TODO: Implement this
  ListNode dummy(0);
  dummy.next = head;
  ListNode *fast = &dummy;
  ListNode *slow = &dummy;

  for (int i = 0; i <= n; i++)
  {
    fast = fast->next;
  }

  while (fast)
  {
    fast = fast->next;
    slow = slow->next;
  }

  ListNode *toDelete = slow->next;
  slow->next = slow->next->next;
  delete toDelete;

  return dummy.next;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Two Pointers with Gap of n

    Use a dummy node to handle edge cases (e.g., removing head).

    1. Move `fast` pointer n+1 steps ahead from dummy
       (so there's a gap of n+1 between fast and slow)
    2. Move both fast and slow until fast reaches null
    3. slow is now at the node BEFORE the one to delete
    4. Skip the target node: slow->next = slow->next->next

    Why n+1 gap? Because we want slow to stop at the node
    BEFORE the one to remove.

    Example: 1->2->3->4->5, n=2
      dummy -> 1 -> 2 -> 3 -> 4 -> 5 -> null

      fast moves n+1=3 steps: fast at node 3
      slow at dummy

      Move together:
        fast=4, slow=1
        fast=5, slow=2
        fast=null, slow=3

      slow->next = slow->next->next => 3->next = 5
      Result: 1 -> 2 -> 3 -> 5

    Time Complexity:  O(n) — single pass
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        // Move fast n+1 steps ahead
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }

        // Move both until fast reaches end
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }

        // Remove the nth node from end
        ListNode* toDelete = slow->next;
        slow->next = slow->next->next;
        delete toDelete;

        return dummy.next;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr[] = {1, 2, 3, 4, 5};
  ListNode *head = buildList(arr, 5);
  cout << "Original: ";
  printList(head);

  head = removeNthFromEnd(head, 2);
  cout << "Remove 2nd from end: ";
  printList(head);
  // Expected: 1 -> 2 -> 3 -> 5

  freeList(head);
  return 0;
}
