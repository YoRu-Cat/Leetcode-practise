// ============================================================
// Problem: Reverse Linked List
// Link: https://leetcode.com/problems/reverse-linked-list/
// ============================================================
// Given the head of a singly linked list, reverse the list,
// and return the reversed list.
// Example: 1->2->3->4->5 => 5->4->3->2->1
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
ListNode *reverseList(ListNode *head)
{
  // TODO: Implement this
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
  return nullptr;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH 1: Iterative (Three Pointers)

    Use three pointers: prev, curr, next
    At each step:
      1. Save curr->next in a temp variable
      2. Point curr->next to prev (reverse the link)
      3. Move prev to curr
      4. Move curr to the saved next

    Visualization:
      null <- 1    2 -> 3 -> 4 -> 5
             prev curr

      null <- 1 <- 2    3 -> 4 -> 5
                  prev  curr

      ... and so on until curr is null

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE (Iterative):
    ListNode* reverseList(ListNode* head) {
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

    ---------------------------------------------------

    APPROACH 2: Recursive

    Base case: if head is null or only one node, return head.
    Recursive step: reverse the rest of the list, then fix the pointers.

    Example: 1 -> 2 -> 3 -> null
      reverseList(1) calls reverseList(2)
        reverseList(2) calls reverseList(3)
          reverseList(3) returns 3 (base case, single node)
        Back in reverseList(2): head=2, head->next=3
          3->next = 2  (reverse link)
          2->next = null (break forward link)
          return 3
      Back in reverseList(1): head=1, head->next=2
          2->next = 1
          1->next = null
          return 3
    Result: 3 -> 2 -> 1 -> null

    SOLUTION CODE (Recursive):
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr[] = {1, 2, 3, 4, 5};
  ListNode *head = buildList(arr, 5);
  cout << "Original: ";
  printList(head);

  head = reverseList(head);
  cout << "Reversed: ";
  printList(head);
  // Expected: 5 -> 4 -> 3 -> 2 -> 1

  freeList(head);
  return 0;
}
