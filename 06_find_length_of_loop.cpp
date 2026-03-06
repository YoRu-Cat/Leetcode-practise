// ============================================================
// Problem: Find Length of Loop
// Link: https://www.geeksforgeeks.org/problems/find-length-of-loop/0
// ============================================================
// Given head of a linked list, if there is a loop, find the
// length of the loop. If no loop, return 0.
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
int countLoopLength(ListNode *head)
{
  // TODO: Implement this
  ListNode *slow = head;
  ListNode *fast = head;
  while (fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast)
    {
      int count = 1;
      ListNode *temp = slow->next;
      while (temp != slow)
      {
        count++;
        temp = temp->next;
      }
      return count;
    }
  }
  return 0;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Floyd's Detection + Count

    Step 1: Use Floyd's algorithm to detect if a cycle exists.
            If slow == fast => they're inside the cycle.

    Step 2: From the meeting point, keep one pointer fixed and
            move the other pointer one step at a time, counting
            steps until it comes back to the same node.

    Example: 1 -> 2 -> 3 -> 4 -> 5 -> (back to 3)
      Cycle: 3 -> 4 -> 5 -> 3  (length = 3)
      After detection, fix `fast`, move `slow`:
        slow = slow->next, count=1  (at 4)
        slow = slow->next, count=2  (at 5)
        slow = slow->next, count=3  (back to 3 = fast) => loop length = 3

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    int countLoopLength(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        // Detect cycle
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                // Count loop length
                int count = 1;
                ListNode* temp = slow->next;
                while (temp != slow) {
                    count++;
                    temp = temp->next;
                }
                return count;
            }
        }
        return 0; // no loop
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // 1 -> 2 -> 3 -> 4 -> 5 -> (back to index 2, which is node 3)
  // Cycle: 3 -> 4 -> 5 -> 3, length = 3
  int arr[] = {1, 2, 3, 4, 5};
  ListNode *head = buildListWithCycle(arr, 5, 2);

  cout << "Loop length: " << countLoopLength(head) << endl;
  // Expected: 3

  // No cycle test
  int arr2[] = {1, 2, 3};
  ListNode *head2 = buildListWithCycle(arr2, 3, -1);
  cout << "Loop length: " << countLoopLength(head2) << endl;
  // Expected: 0

  return 0;
}
