// ============================================================
// Problem: Odd Even Linked List
// Link: https://leetcode.com/problems/odd-even-linked-list/
// ============================================================
// Given the head of a singly linked list, group all the nodes
// with odd indices together followed by the nodes with even indices.
// The first node is index 1 (odd), second is index 2 (even), etc.
// Must solve in O(1) extra space and O(n) time.
// Example: 1->2->3->4->5 => 1->3->5->2->4
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
  return nullptr;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Two Pointers — Separate Odd and Even Chains

    Maintain two pointers:
      - odd: traverses the odd-indexed nodes
      - even: traverses the even-indexed nodes

    Save the head of the even list. After separating, attach
    the even list to the end of the odd list.

    Walkthrough: 1 -> 2 -> 3 -> 4 -> 5
      odd = 1, even = 2, evenHead = 2

      Step 1: odd->next = 3,  odd = 3   | even->next = 4, even = 4
              Odd chain:  1 -> 3         | Even chain: 2 -> 4
      Step 2: odd->next = 5,  odd = 5   | even->next = null, even = null
              Odd chain:  1 -> 3 -> 5    | Even chain: 2 -> 4

      Link: odd->next = evenHead
      Result: 1 -> 3 -> 5 -> 2 -> 4

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
  int arr[] = {1, 2, 3, 4, 5};
  ListNode *head = buildList(arr, 5);
  cout << "Original: ";
  printList(head);

  head = oddEvenList(head);
  cout << "Odd-Even: ";
  printList(head);
  // Expected: 1 -> 3 -> 5 -> 2 -> 4

  freeList(head);
  return 0;
}
