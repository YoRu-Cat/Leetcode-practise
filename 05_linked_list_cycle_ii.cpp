// ============================================================
// Problem: Linked List Cycle II
// Link: https://leetcode.com/problems/linked-list-cycle-ii/
// ============================================================
// Given the head of a linked list, return the node where the
// cycle begins. If there is no cycle, return null.
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
    curr->next = cycleNode;
  return head;
}

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
ListNode *detectCycle(ListNode *head)
{
  ListNode *slow = head;
  ListNode *fast = head;
  while (fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast)
    {
      slow = head;
      while (slow != fast)
      {
        slow = slow->next;
        fast = fast->next;
      }
      return slow; // cycle start
    }
  }
  return nullptr;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Floyd's Cycle Detection — Phase 2

    Phase 1: Detect if cycle exists (same as Linked List Cycle I)
      - slow moves 1 step, fast moves 2 steps
      - If they meet => cycle exists

    Phase 2: Find the START of the cycle
      - Reset one pointer to head
      - Move both pointers 1 step at a time
      - Where they meet = start of cycle

    MATHEMATICAL PROOF:
      Let:
        L = distance from head to cycle start
        C = cycle length
        K = distance from cycle start to meeting point

      When they meet:
        slow traveled: L + K
        fast traveled: L + K + n*C  (n = number of full loops fast made)

      Since fast travels 2x slow:
        2(L + K) = L + K + n*C
        L + K = n*C
        L = n*C - K

      This means: if we start one pointer at head and one at the
      meeting point, and move both 1 step at a time, they'll meet
      at the cycle start (distance L from both starting positions).

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* detectCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        // Phase 1: Detect cycle
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                // Phase 2: Find cycle start
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow; // cycle start
            }
        }
        return nullptr; // no cycle
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // 3 -> 2 -> 0 -> -4 -> (back to node at index 1, which is 2)
  int arr[] = {3, 2, 0, -4};
  ListNode *head = buildListWithCycle(arr, 4, 1);

  ListNode *cycleStart = detectCycle(head);
  if (cycleStart)
    cout << "Cycle starts at node with value: " << cycleStart->val << endl;
  else
    cout << "No cycle" << endl;
  // Expected: Cycle starts at node with value: 2

  return 0;
}
