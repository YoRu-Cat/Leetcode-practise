// ============================================================
// Problem: Add 1 to a Linked List Number
// Link: https://www.geeksforgeeks.org/problems/add-1-to-a-number-represented-as-linked-list/0
// ============================================================
// A number is represented by a linked list, with the head
// being the most significant digit. Add 1 to it.
// Example: 1->9->9 represents 199, add 1 => 2->0->0 (200)
//          9->9->9 represents 999, add 1 => 1->0->0->0 (1000)
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
ListNode *reverseLL(ListNode *head)
{
  ListNode *prev = nullptr;
  ListNode *curr = head;
  while (curr)
  {
    ListNode *next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}

ListNode *addOne(ListNode *head)
{
  // TODO: Implement this
  head = reverseLL(head);

  ListNode *curr = head;
  int carry = 1;
  while (curr)
  {
    int sum = curr->val + carry;
    curr->val = sum % 10;
    carry = sum / 10;
    if (!curr->next && carry)
    {
      curr->next = new ListNode(carry);
      carry = 0;
    }
    curr = curr->next;
  }

  head = reverseLL(head);
  return head;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Reverse, Add, Reverse Back

    Since addition propagates carry from the least significant
    digit (tail) to the most significant (head), and we only
    have forward pointers, we reverse the list first.

    Steps:
      1. Reverse the linked list
      2. Add 1, propagating carry
      3. If carry remains after traversal, add a new node
      4. Reverse the list back

    Example: 1 -> 9 -> 9
      Reverse: 9 -> 9 -> 1
      Add 1:   9+1=10, set to 0, carry=1
               9+1=10, set to 0, carry=1
               1+1=2,  set to 2, carry=0
      List:    0 -> 0 -> 2
      Reverse: 2 -> 0 -> 0  ✓ (200)

    Example: 9 -> 9 -> 9
      Reverse: 9 -> 9 -> 9
      Add 1:   0, carry=1 -> 0, carry=1 -> 0, carry=1
      Carry=1: add new node(1)
      List:    0 -> 0 -> 0 -> 1
      Reverse: 1 -> 0 -> 0 -> 0  ✓ (1000)

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* reverse(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    ListNode* addOne(ListNode* head) {
        // Step 1: Reverse
        head = reverse(head);

        // Step 2: Add 1
        ListNode* curr = head;
        int carry = 1;
        while (curr) {
            int sum = curr->val + carry;
            curr->val = sum % 10;
            carry = sum / 10;
            if (!curr->next && carry) {
                curr->next = new ListNode(carry);
                carry = 0;
            }
            curr = curr->next;
        }

        // Step 3: Reverse back
        return reverse(head);
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr1[] = {1, 9, 9};
  ListNode *head1 = buildList(arr1, 3);
  cout << "Number: ";
  printList(head1);
  head1 = addOne(head1);
  cout << "Plus 1: ";
  printList(head1);
  // Expected: 2 -> 0 -> 0

  int arr2[] = {9, 9, 9};
  ListNode *head2 = buildList(arr2, 3);
  cout << "Number: ";
  printList(head2);
  head2 = addOne(head2);
  cout << "Plus 1: ";
  printList(head2);
  // Expected: 1 -> 0 -> 0 -> 0

  freeList(head1);
  freeList(head2);
  return 0;
}
