// ============================================================
// Problem: Sort a Linked List of 0s, 1s, and 2s
// Link: https://www.geeksforgeeks.org/problems/given-a-linked-list-of-0s-1s-and-2s-sort-it/0
// ============================================================
// Given a linked list of 0s, 1s, and 2s, sort it.
// Example: 1->2->2->1->2->0->2->2 => 0->1->1->2->2->2->2->2
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
ListNode *sortList012(ListNode *head)
{
  // TODO: Implement this
  ListNode d0(0), d1(0), d2(0);
  ListNode *t0 = &d0, *t1 = &d1, *t2 = &d2;

  ListNode *curr = head;
  while (curr)
  {
    if (curr->val == 0)
    {
      t0->next = curr;
      t0 = t0->next;
    }
    else if (curr->val == 1)
    {
      t1->next = curr;
      t1 = t1->next;
    }
    else
    {
      t2->next = curr;
      t2 = t2->next;
    }
    curr = curr->next;
  }

  t0->next = (d1.next) ? d1.next : d2.next;
  t1->next = d2.next;
  t2->next = nullptr;

  return d0.next;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Three Dummy Heads (Dutch National Flag for Linked Lists)

    Create three separate lists: one for 0s, one for 1s, one for 2s.
    Traverse the original list and append each node to the correct list.
    Then connect: 0s list -> 1s list -> 2s list.

    Use dummy heads for each list to simplify appending.

    Example: 1 -> 2 -> 0 -> 1 -> 2
      zeros:  dummy0 -> 0
      ones:   dummy1 -> 1 -> 1
      twos:   dummy2 -> 2 -> 2

      Connect: 0 -> 1 -> 1 -> 2 -> 2 -> null
      Return dummy0->next

    Handle empty sublists carefully when connecting:
      - If zeros list is empty, head is ones list
      - If ones list is empty, zeros list connects to twos list

    Time Complexity:  O(n)
    Space Complexity: O(1) — just rearranging existing nodes

    SOLUTION CODE:
    ListNode* sortList012(ListNode* head) {
        ListNode d0(0), d1(0), d2(0); // dummy heads
        ListNode* t0 = &d0, *t1 = &d1, *t2 = &d2;

        ListNode* curr = head;
        while (curr) {
            if (curr->val == 0) { t0->next = curr; t0 = t0->next; }
            else if (curr->val == 1) { t1->next = curr; t1 = t1->next; }
            else { t2->next = curr; t2 = t2->next; }
            curr = curr->next;
        }

        // Connect the three lists
        t0->next = (d1.next) ? d1.next : d2.next;
        t1->next = d2.next;
        t2->next = nullptr;

        return d0.next;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr[] = {1, 2, 2, 1, 2, 0, 2, 2};
  ListNode *head = buildList(arr, 8);
  cout << "Original: ";
  printList(head);

  head = sortList012(head);
  cout << "Sorted:   ";
  printList(head);
  // Expected: 0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2

  freeList(head);
  return 0;
}
