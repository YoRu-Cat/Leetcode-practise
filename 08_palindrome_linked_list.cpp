// ============================================================
// Problem: Palindrome Linked List
// Link: https://leetcode.com/problems/palindrome-linked-list/
// ============================================================
// Given the head of a singly linked list, return true if it is
// a palindrome (reads the same forward and backward).
// Example: 1->2->2->1 => true
//          1->2->3 => false
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
bool isPalindrome(ListNode *head)
{
  // TODO: Implement this
  if (!head || !head->next)
    return true;

  // Step 1: Find middle
  ListNode *slow = head;
  ListNode *fast = head;
  while (fast->next && fast->next->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }

  // Step 2: Reverse second half (starting from slow->next)
  ListNode *prev = nullptr;
  ListNode *curr = slow->next;
  while (curr)
  {
    ListNode *next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  // prev is now head of reversed second half

  // Step 3: Compare
  ListNode *first = head;
  ListNode *second = prev;
  while (second)
  {
    if (first->val != second->val)
      return false;
    first = first->next;
    second = second->next;
  }
  return true;
  return false;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Find Middle + Reverse Second Half + Compare

    Steps:
      1. Find the middle of the list using slow/fast pointers
      2. Reverse the second half of the list
      3. Compare the first half with the reversed second half
      4. (Optional) Restore the list by reversing second half again

    Example: 1 -> 2 -> 3 -> 2 -> 1
      Step 1: Middle is node 3. slow at 3.
      Step 2: Reverse from 3->next onwards: 1 -> 2 -> null
              First half:  1 -> 2 -> 3
              Second half: 1 -> 2 -> null
      Step 3: Compare: 1==1 ✓, 2==2 ✓ => palindrome!

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;

        // Step 1: Find middle
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Reverse second half (starting from slow->next)
        ListNode* prev = nullptr;
        ListNode* curr = slow->next;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        // prev is now head of reversed second half

        // Step 3: Compare
        ListNode* first = head;
        ListNode* second = prev;
        while (second) {
            if (first->val != second->val) return false;
            first = first->next;
            second = second->next;
        }
        return true;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr1[] = {1, 2, 3, 2, 1};
  ListNode *head1 = buildList(arr1, 5);
  cout << "List: ";
  printList(head1);
  cout << "Palindrome: " << (isPalindrome(head1) ? "true" : "false") << endl;
  // Expected: true

  int arr2[] = {1, 2, 3, 4};
  ListNode *head2 = buildList(arr2, 4);
  cout << "List: ";
  printList(head2);
  cout << "Palindrome: " << (isPalindrome(head2) ? "true" : "false") << endl;
  // Expected: false

  return 0;
}
