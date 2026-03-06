// ============================================================
// Problem: Odd Even Linked List
// Link: https://leetcode.com/problems/odd-even-linked-list/
// ============================================================
// Given the head of a singly linked list, group all the nodes
// with ODD indices together followed by nodes with EVEN indices.
// (1-indexed: first node is odd, second is even, etc.)
// Relative order within each group must be preserved.
// Must solve in O(1) extra space and O(n) time.
// Example: 1->2->3->4->5 => 1->3->5->2->4
// Example: 2->1->3->5->6->4->7 => 2->3->6->7->1->5->4
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
ListNode *oddEvenList(ListNode *head)
{
  // TODO: Implement this
  if (!head || !head->next)
    return head;

  ListNode *odd = head;
  ListNode *even = head->next;
  ListNode *evenHead = even;

  while (even && even->next)
  {
    odd->next = even->next;
    odd = odd->next;
    even->next = odd->next;
    even = even->next;
  }

  odd->next = evenHead;
  return head;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Two Pointers — Odd and Even chains

    Keep two pointers: odd and even.
    - odd  starts at node 1 (head)
    - even starts at node 2 (head->next)
    Save evenHead = even so we can connect later.

    In each iteration, skip one node for each:
      odd->next  = even->next   (link odd to next odd)
      odd = odd->next
      even->next = odd->next    (link even to next even)
      even = even->next

    Finally: odd->next = evenHead

    Walkthrough: 1->2->3->4->5
      odd=1, even=2, evenHead=2

      Iter 1: odd->next = 3, odd=3 | even->next = 4, even=4
        odd chain:  1->3
        even chain: 2->4

      Iter 2: odd->next = 5, odd=5 | even->next = null, even=null
        odd chain:  1->3->5
        even chain: 2->4

      Loop ends (even==null).
      Connect: 5->next = evenHead(2)
      Result: 1->3->5->2->4 ✓

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* evenHead = even;

        while (even && even->next) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }

        odd->next = evenHead;
        return head;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // Test 1
  int arr1[] = {1, 2, 3, 4, 5};
  ListNode *h1 = buildList(arr1, 5);
  cout << "Original: ";
  printList(h1);
  h1 = oddEvenList(h1);
  cout << "Odd-Even: ";
  printList(h1);
  // Expected: 1 -> 3 -> 5 -> 2 -> 4
  freeList(h1);

  cout << endl;

  // Test 2
  int arr2[] = {2, 1, 3, 5, 6, 4, 7};
  ListNode *h2 = buildList(arr2, 7);
  cout << "Original: ";
  printList(h2);
  h2 = oddEvenList(h2);
  cout << "Odd-Even: ";
  printList(h2);
  // Expected: 2 -> 3 -> 6 -> 7 -> 1 -> 5 -> 4
  freeList(h2);

  return 0;
}
