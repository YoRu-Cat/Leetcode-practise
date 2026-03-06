// ============================================================
// Problem: Swap Nodes in Pairs
// Link: https://leetcode.com/problems/swap-nodes-in-pairs/
// ============================================================
// Given a linked list, swap every two adjacent nodes and
// return the new head. You must solve it without modifying
// the values, only rearranging the nodes themselves.
// Example: 1->2->3->4 => 2->1->4->3
// Example: 1->2->3 => 2->1->3
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
ListNode *swapPairs(ListNode *head)
{
  // TODO: Implement this
  ListNode dummy(0);
  dummy.next = head;
  ListNode *prev = &dummy;

  while (prev->next && prev->next->next)
  {
    ListNode *A = prev->next;
    ListNode *B = A->next;

    prev->next = B;
    A->next = B->next;
    B->next = A;

    prev = A;
  }

  return dummy.next;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Iterative with Dummy Node

    Use a dummy node before head. For every pair of nodes, swap them
    by rearranging pointers.

    prev -> A -> B -> C -> ...
    After swap:
    prev -> B -> A -> C -> ...
    Then move prev to A (which is now second).

    Walkthrough: 1->2->3->4

    dummy -> 1 -> 2 -> 3 -> 4
    prev=dummy, A=1, B=2

    Swap: prev->next = B (2)
           A->next = B->next (3)
           B->next = A (1)
    Result: dummy -> 2 -> 1 -> 3 -> 4
    Move prev to A (which is node 1).

    prev=1, A=3, B=4
    Swap: prev->next = B (4)
           A->next = B->next (null)
           B->next = A (3)
    Result: dummy -> 2 -> 1 -> 4 -> 3
    Move prev to A (which is node 3).

    prev=3, A=null => stop.
    Return dummy->next = 2->1->4->3 ✓

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prev = &dummy;

        while (prev->next && prev->next->next) {
            ListNode* A = prev->next;
            ListNode* B = A->next;

            prev->next = B;
            A->next = B->next;
            B->next = A;

            prev = A;   // A is now the second node in the pair
        }

        return dummy.next;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // Test 1: Even length
  int arr1[] = {1, 2, 3, 4};
  ListNode *h1 = buildList(arr1, 4);
  cout << "Original: ";
  printList(h1);
  h1 = swapPairs(h1);
  cout << "Swapped:  ";
  printList(h1);
  // Expected: 2 -> 1 -> 4 -> 3
  freeList(h1);

  cout << endl;

  // Test 2: Odd length
  int arr2[] = {1, 2, 3};
  ListNode *h2 = buildList(arr2, 3);
  cout << "Original: ";
  printList(h2);
  h2 = swapPairs(h2);
  cout << "Swapped:  ";
  printList(h2);
  // Expected: 2 -> 1 -> 3
  freeList(h2);

  return 0;
}
