// ============================================================
// Problem: Reverse Nodes in k-Group
// Link: https://leetcode.com/problems/reverse-nodes-in-k-group/
// ============================================================
// Given the head of a linked list, reverse the nodes of the list
// k at a time, and return the modified list.
// If the number of nodes is not a multiple of k, leave the
// remaining nodes as they are.
// Example: 1->2->3->4->5, k=2 => 2->1->4->3->5
//          1->2->3->4->5, k=3 => 3->2->1->4->5
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
  if (!head || k == 1)
    return head;

  // Dummy node
  ListNode dummy(0);
  dummy.next = head;
  ListNode *prevGroupEnd = &dummy;

  while (true)
  {
    // Check if k nodes exist from prevGroupEnd->next
    ListNode *kthNode = prevGroupEnd;
    for (int i = 0; i < k; i++)
    {
      kthNode = kthNode->next;
      if (!kthNode)
        return dummy.next; // less than k nodes left
    }

    ListNode *groupStart = prevGroupEnd->next;
    ListNode *nextGroupStart = kthNode->next;

    // Reverse k nodes starting from groupStart
    ListNode *prev = nextGroupStart; // reversed group's last node points here
    ListNode *curr = groupStart;
    for (int i = 0; i < k; i++)
    {
      ListNode *next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }

    // Connect previous group to new head of this reversed group
    prevGroupEnd->next = kthNode; // kthNode is now the head after reversal
    prevGroupEnd = groupStart;    // groupStart is now the tail
  }

  return dummy.next;
  return nullptr;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Iterative Group Reversal

    For each group of k nodes:
      1. Check if there are k nodes remaining. If not, stop.
      2. Reverse those k nodes.
      3. Connect the reversed group to the previous group's tail.
      4. Move to the next group.

    We use a dummy node before head to simplify edge cases.

    Detailed walkthrough for [1,2,3,4,5], k=2:
      dummy -> 1 -> 2 -> 3 -> 4 -> 5

      Group 1: reverse [1,2] => dummy -> 2 -> 1 -> 3 -> 4 -> 5
        prevGroupEnd = dummy, groupStart = 1, groupEnd = 2
        After reverse: prevGroupEnd->next = 2, 1->next = 3
        prevGroupEnd = 1 (the old groupStart, now at end of reversed group)

      Group 2: reverse [3,4] => dummy -> 2 -> 1 -> 4 -> 3 -> 5
        groupStart = 3, groupEnd = 4
        After reverse: 1->next = 4, 3->next = 5
        prevGroupEnd = 3

      Group 3: only 1 node (5), less than k=2, stop.

    Time Complexity:  O(n)
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) return head;

        // Dummy node
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prevGroupEnd = &dummy;

        while (true) {
            // Check if k nodes exist from prevGroupEnd->next
            ListNode* kthNode = prevGroupEnd;
            for (int i = 0; i < k; i++) {
                kthNode = kthNode->next;
                if (!kthNode) return dummy.next; // less than k nodes left
            }

            ListNode* groupStart = prevGroupEnd->next;
            ListNode* nextGroupStart = kthNode->next;

            // Reverse k nodes starting from groupStart
            ListNode* prev = nextGroupStart; // reversed group's last node points here
            ListNode* curr = groupStart;
            for (int i = 0; i < k; i++) {
                ListNode* next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            // Connect previous group to new head of this reversed group
            prevGroupEnd->next = kthNode; // kthNode is now the head after reversal
            prevGroupEnd = groupStart;    // groupStart is now the tail
        }

        return dummy.next;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int arr[] = {1, 2, 3, 4, 5};

  ListNode *head1 = buildList(arr, 5);
  cout << "Original: ";
  printList(head1);
  head1 = reverseKGroup(head1, 2);
  cout << "k=2:      ";
  printList(head1);
  // Expected: 2 -> 1 -> 4 -> 3 -> 5

  ListNode *head2 = buildList(arr, 5);
  head2 = reverseKGroup(head2, 3);
  cout << "k=3:      ";
  printList(head2);
  // Expected: 3 -> 2 -> 1 -> 4 -> 5

  freeList(head1);
  freeList(head2);
  return 0;
}
