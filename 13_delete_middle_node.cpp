// ============================================================
// Problem: Delete the Middle Node of a Linked List
// Link: https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
// ============================================================
// Given the head of a linked list, delete the middle node and
// return the head. The middle node is at index n/2 (0-indexed)
// where n is the number of nodes.
// Example: 1->3->4->7->1->2->6 => 1->3->4->1->2->6 (removed 7)
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
ListNode *deleteMiddle(ListNode *head)
{
  // TODO: Implement this
  if (!head || !head->next)
    return nullptr;

  ListNode *slow = head;
  ListNode *fast = head->next->next;

  while (fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode *mid = slow->next;
  slow->next = mid->next;
  delete mid;

  return head;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Slow/Fast Pointers — Stop Before Middle

    Similar to finding the middle, but we need the node BEFORE
    the middle so we can skip it.

    Use a dummy node, or start slow one step behind:
      - slow starts at a node before head (using prev pointer)
      - OR use fast starting 2 steps ahead

    Trick: Start fast from head->next->next (2 steps ahead).
    When fast reaches end, slow is just before the middle.

    Example: 1 -> 3 -> 4 -> 7 -> 1 -> 2 -> 6 (7 nodes, middle at index 3 = node 7)
      slow = 1, fast = 4
      slow = 3, fast = 1
      slow = 4, fast = 6
      fast->next is null => stop
      slow->next (7) is the middle => skip it
      4->next = 1
      Result: 1 -> 3 -> 4 -> 1 -> 2 -> 6

    Edge case: single node => return null

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* deleteMiddle(ListNode* head) {
        if (!head || !head->next) return nullptr; // single node or empty

        ListNode* slow = head;
        ListNode* fast = head->next->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // slow is now the node before the middle
        ListNode* mid = slow->next;
        slow->next = mid->next;
        delete mid;

        return head;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr[] = {1, 3, 4, 7, 1, 2, 6};
  ListNode *head = buildList(arr, 7);
  cout << "Original: ";
  printList(head);

  head = deleteMiddle(head);
  cout << "After deleting middle: ";
  printList(head);
  // Expected: 1 -> 3 -> 4 -> 1 -> 2 -> 6

  freeList(head);
  return 0;
}
