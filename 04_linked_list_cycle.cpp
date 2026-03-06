// ============================================================
// Problem: Linked List Cycle
// Link: https://leetcode.com/problems/linked-list-cycle/
// ============================================================
// Given head, determine if the linked list has a cycle in it.
// A cycle exists if some node's next pointer points back to a
// previously visited node. Return true if cycle exists, else false.
// ============================================================

#include <iostream>
using namespace std;

// -------------------- Boilerplate --------------------
struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

// Helper: Build list with optional cycle (cycleTo = index of node tail connects to, -1 for no cycle)
ListNode *buildListWithCycle(int arr[], int n, int cycleTo)
{
  if (n == 0)
    return nullptr;
  ListNode *head = new ListNode(arr[0]);
  ListNode *curr = head;
  ListNode *cycleNode = (cycleTo == 0) ? head : nullptr;
  for (int i = 1; i < n; i++)
  {
    curr->next = new ListNode(arr[i]);
    curr = curr->next;
    if (i == cycleTo)
      cycleNode = curr;
  }
  if (cycleTo >= 0 && cycleNode)
    curr->next = cycleNode; // create cycle
  return head;
}

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:

bool hasCycle(ListNode *head)
{
  ListNode *slow = head;
  ListNode *fast = head;
  while (fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast)
      return true;
  }
  return false;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Floyd's Cycle Detection (Tortoise & Hare)

    Use two pointers:
      - slow moves 1 step
      - fast moves 2 steps

    If there's a cycle, fast will eventually "lap" slow and they'll
    meet at some node inside the cycle.

    If there's no cycle, fast will reach null.

    Why they must meet:
      Once both are in the cycle, the gap between fast and slow
      decreases by 1 each step. So they MUST collide.

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // Test 1: List with cycle: 3 -> 2 -> 0 -> -4 -> (back to 2)
  int arr1[] = {3, 2, 0, -4};
  ListNode *head1 = buildListWithCycle(arr1, 4, 1); // tail connects to index 1
  cout << "Has cycle: " << (hasCycle(head1) ? "true" : "false") << endl;
  // Expected: true

  // Test 2: No cycle: 1 -> 2 -> 3
  int arr2[] = {1, 2, 3};
  ListNode *head2 = buildListWithCycle(arr2, 3, -1);
  cout << "Has cycle: " << (hasCycle(head2) ? "true" : "false") << endl;
  // Expected: false

  // Don't free cyclic list (would loop forever without tracking visited)
  return 0;
}
