// ============================================================
// Problem: Split Linked List in Parts
// Link: https://leetcode.com/problems/split-linked-list-in-parts/
// ============================================================
// Given a singly linked list and an integer k, split the list
// into k consecutive parts. Parts should be as equal as possible:
// no two parts should differ by more than 1 node, and earlier
// parts should be larger.
// Example: 1->2->3, k=5 => [[1],[2],[3],[],[]]
// Example: 1->2->3->4->5->6->7->8->9->10, k=3
//          => [[1,2,3,4],[5,6,7],[8,9,10]]
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
  if (!head)
  {
    cout << "(empty)";
    return;
  }
  while (head)
  {
    cout << head->val;
    if (head->next)
      cout << " -> ";
    head = head->next;
  }
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
// Note: Returns an array of k ListNode* pointers (heads of each part).
// For simplicity we use a fixed max k.
const int MAX_K = 100;
ListNode *result[MAX_K];

void splitListToParts(ListNode *head, int k)
{
  // TODO: populate result[0..k-1] with heads of each part
  int n = 0;
  ListNode *curr = head;
  while (curr)
  {
    n++;
    curr = curr->next;
  }

  int base = n / k;
  int extra = n % k;

  curr = head;
  for (int i = 0; i < k; i++)
  {
    result[i] = curr;
    int partSize = base + (i < extra ? 1 : 0);

    for (int j = 1; j < partSize; j++)
    {
      curr = curr->next;
    }

    if (curr)
    {
      ListNode *nxt = curr->next;
      curr->next = nullptr;
      curr = nxt;
    }
  }
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Calculate sizes, then cut

    1. Find total length n.
    2. Each part gets at least n/k nodes.
       The first (n % k) parts get 1 extra node.
    3. Traverse and cut the list at the right points.

    Walkthrough: 1->2->3->4->5->6->7->8->9->10, k=3
      n = 10
      base = 10/3 = 3       (each part gets at least 3)
      extra = 10%3 = 1       (first 1 part gets 4)

      Part 0: size = 3+1 = 4 => [1,2,3,4]
      Part 1: size = 3+0 = 3 => [5,6,7]
      Part 2: size = 3+0 = 3 => [8,9,10]

    Walkthrough: 1->2->3, k=5
      n = 3
      base = 3/5 = 0
      extra = 3%5 = 3

      Part 0: size = 0+1 = 1 => [1]
      Part 1: size = 0+1 = 1 => [2]
      Part 2: size = 0+1 = 1 => [3]
      Part 3: size = 0+0 = 0 => []
      Part 4: size = 0+0 = 0 => []

    Time Complexity:  O(n + k)
    Space Complexity: O(k) for the output array

    SOLUTION CODE:
    void splitListToParts(ListNode* head, int k) {
        // Find length
        int n = 0;
        ListNode* curr = head;
        while (curr) { n++; curr = curr->next; }

        int base = n / k;      // minimum nodes per part
        int extra = n % k;     // first 'extra' parts get 1 more

        curr = head;
        for (int i = 0; i < k; i++) {
            result[i] = curr;
            int partSize = base + (i < extra ? 1 : 0);

            // Advance (partSize - 1) steps to reach the tail of this part
            for (int j = 1; j < partSize; j++) {
                curr = curr->next;
            }

            // Cut
            if (curr) {
                ListNode* nxt = curr->next;
                curr->next = nullptr;
                curr = nxt;
            }
        }
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  // Test 1: More parts than nodes
  int arr1[] = {1, 2, 3};
  ListNode *h1 = buildList(arr1, 3);
  cout << "Original: ";
  printList(h1);
  cout << endl;
  int k1 = 5;
  splitListToParts(h1, k1);
  cout << "Split into " << k1 << " parts:" << endl;
  for (int i = 0; i < k1; i++)
  {
    cout << "  Part " << i << ": ";
    printList(result[i]);
    cout << endl;
  }
  // Expected: [1], [2], [3], (empty), (empty)
  for (int i = 0; i < k1; i++)
    freeList(result[i]);

  cout << endl;

  // Test 2: Even split with remainder
  int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ListNode *h2 = buildList(arr2, 10);
  cout << "Original: ";
  printList(h2);
  cout << endl;
  int k2 = 3;
  splitListToParts(h2, k2);
  cout << "Split into " << k2 << " parts:" << endl;
  for (int i = 0; i < k2; i++)
  {
    cout << "  Part " << i << ": ";
    printList(result[i]);
    cout << endl;
  }
  // Expected: [1,2,3,4], [5,6,7], [8,9,10]
  for (int i = 0; i < k2; i++)
    freeList(result[i]);

  return 0;
}
