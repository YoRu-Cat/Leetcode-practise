// ============================================================
// Problem: Add Two Numbers
// Link: https://leetcode.com/problems/add-two-numbers/
// ============================================================
// Two non-negative integers are represented as linked lists
// where each node contains a single digit, stored in REVERSE order.
// Add them and return the sum as a linked list.
// Example: (2->4->3) + (5->6->4) = 7->0->8  (342 + 465 = 807)
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
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
  // TODO: Implement this
  ListNode dummy;
  ListNode *curr = &dummy;
  int carry = 0;

  while (l1 || l2 || carry)
  {
    int sum = carry;
    if (l1)
    {
      sum += l1->val;
      l1 = l1->next;
    }
    if (l2)
    {
      sum += l2->val;
      l2 = l2->next;
    }
    carry = sum / 10;
    curr->next = new ListNode(sum % 10);
    curr = curr->next;
  }

  return dummy.next;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Elementary Addition with Carry

    Since digits are stored in REVERSE order (least significant first),
    we can add them directly left to right, just like manual addition.

    Use a dummy head to build the result list.
    Keep a carry variable (0 or 1).

    For each position:
      sum = (l1->val or 0) + (l2->val or 0) + carry
      new digit = sum % 10
      carry = sum / 10

    Continue until both lists are exhausted AND carry is 0.

    Example: 2->4->3  (342)
           + 5->6->4  (465)
    Position 0: 2+5+0 = 7, carry=0 => node(7)
    Position 1: 4+6+0 = 10, carry=1 => node(0)
    Position 2: 3+4+1 = 8, carry=0 => node(8)
    Result: 7->0->8 (807) ✓

    Time Complexity:  O(max(m, n))
    Space Complexity: O(max(m, n)) for the result

    SOLUTION CODE:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* curr = &dummy;
        int carry = 0;

        while (l1 || l2 || carry) {
            int sum = carry;
            if (l1) { sum += l1->val; l1 = l1->next; }
            if (l2) { sum += l2->val; l2 = l2->next; }
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
        }

        return dummy.next;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int a1[] = {2, 4, 3}; // 342
  int a2[] = {5, 6, 4}; // 465
  ListNode *l1 = buildList(a1, 3);
  ListNode *l2 = buildList(a2, 3);

  cout << "Num 1: ";
  printList(l1);
  cout << "Num 2: ";
  printList(l2);

  ListNode *result = addTwoNumbers(l1, l2);
  cout << "Sum:   ";
  printList(result);
  // Expected: 7 -> 0 -> 8 (807)

  freeList(l1);
  freeList(l2);
  freeList(result);
  return 0;
}
