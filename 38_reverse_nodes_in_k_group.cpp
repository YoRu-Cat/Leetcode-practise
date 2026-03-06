// ============================================================
// Problem: Reverse Nodes in k-Group
// Link: https://leetcode.com/problems/reverse-nodes-in-k-group/
// ============================================================
// Given the head of a linked list, reverse the nodes of the
// list k at a time, and return the modified list.
// If the number of remaining nodes < k, leave them as is.
// You may NOT alter the values in the nodes.
// Example: 1->2->3->4->5, k=2 => 2->1->4->3->5
// Example: 1->2->3->4->5, k=3 => 3->2->1->4->5
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
ListNode *reverseKGroup(ListNode *head, int k)
{
  // TODO: Implement this
  ListNode dummy(0);
  dummy.next = head;
  ListNode *prevGroupEnd = &dummy;

  while (true)
  {
    ListNode *checker = prevGroupEnd;
    for (int i = 0; i < k; i++)
    {
      checker = checker->next;
      if (!checker)
        return dummy.next;
    }

    ListNode *first = prevGroupEnd->next;
    ListNode *curr = first->next;

    for (int i = 1; i < k; i++)
    {
      first->next = curr->next;
      curr->next = prevGroupEnd->next;
      prevGroupEnd->next = curr;
      curr = first->next;
    }

    prevGroupEnd = first;
  }
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Iterative — Check then Reverse

    For each group of k nodes:
    1. First check if there are k nodes remaining.
       If not, stop (leave the rest as-is).
    2. Reverse the k nodes in-place.
    3. Connect the previous group's tail to the new head.
    4. Move to the next group.

    We use a dummy node to simplify head management.

    Walkthrough: 1->2->3->4->5, k=3

    dummy -> 1 -> 2 -> 3 -> 4 -> 5
    prevGroupEnd = dummy

    Group 1: Check 3 nodes from 1? Yes (1,2,3).
      Reverse 1->2->3:
        Start: prevGroupEnd->next = 1, we reverse next k-1 links
        After each reversal we pull the next node to front of group:
          Pull 2 before 1: dummy -> 2 -> 1 -> 3 -> 4 -> 5
          Pull 3 before 2: dummy -> 3 -> 2 -> 1 -> 4 -> 5
      prevGroupEnd = 1 (the old first, now group tail)

    Group 2: Check 2 nodes from 4? No (only 4,5 = 2 < 3). Stop.

    Result: 3 -> 2 -> 1 -> 4 -> 5 ✓

    Detailed mechanism for reversing within a group:
    prevGroupEnd -> [first] -> [curr] -> [next] -> ...
    To pull curr to front of group:
      first->next = curr->next
      curr->next = prevGroupEnd->next
      prevGroupEnd->next = curr
    Repeat (k-1) times.

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prevGroupEnd = &dummy;

        while (true) {
            // Check if k nodes remain
            ListNode* checker = prevGroupEnd;
            for (int i = 0; i < k; i++) {
                checker = checker->next;
                if (!checker) return dummy.next;  // fewer than k nodes left
            }

            // Reverse k nodes
            // first is the first node of the group (will become last after reversal)
            ListNode* first = prevGroupEnd->next;
            ListNode* curr = first->next;

            for (int i = 1; i < k; i++) {
                // Pull curr to front of group
                first->next = curr->next;
                curr->next = prevGroupEnd->next;
                prevGroupEnd->next = curr;
                curr = first->next;
            }

            // Move prevGroupEnd to the end of the reversed group
            prevGroupEnd = first;
        }
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // Test 1: k=2
  int arr1[] = {1, 2, 3, 4, 5};
  ListNode *h1 = buildList(arr1, 5);
  cout << "Original: ";
  printList(h1);
  h1 = reverseKGroup(h1, 2);
  cout << "Reverse k=2: ";
  printList(h1);
  // Expected: 2 -> 1 -> 4 -> 3 -> 5
  freeList(h1);

  cout << endl;

  // Test 2: k=3
  int arr2[] = {1, 2, 3, 4, 5};
  ListNode *h2 = buildList(arr2, 5);
  cout << "Original: ";
  printList(h2);
  h2 = reverseKGroup(h2, 3);
  cout << "Reverse k=3: ";
  printList(h2);
  // Expected: 3 -> 2 -> 1 -> 4 -> 5
  freeList(h2);

  cout << endl;

  // Test 3: k=1 (no change)
  int arr3[] = {1, 2, 3};
  ListNode *h3 = buildList(arr3, 3);
  cout << "Original: ";
  printList(h3);
  h3 = reverseKGroup(h3, 1);
  cout << "Reverse k=1: ";
  printList(h3);
  // Expected: 1 -> 2 -> 3
  freeList(h3);

  return 0;
}
