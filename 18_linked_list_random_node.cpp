// ============================================================
// Problem: Linked List Random Node
// Link: https://leetcode.com/problems/linked-list-random-node/
// ============================================================
// Given a singly linked list, return a random node's value.
// Each node must be equally likely to be chosen.
// Implement the Solution class:
//   - Solution(ListNode* head) — initializes with the head
//   - int getRandom() — returns a random node's value
// ============================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
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
class Solution
{
  ListNode *head;

public:
  Solution(ListNode *head)
  {
    // TODO: Initialize
    this->head = head;
    srand(time(0));
  }

  int getRandom()
  {
    // TODO: Implement Reservoir Sampling
    ListNode *curr = head;
    int result = curr->val;
    int i = 1;
    while (curr)
    {
      if (rand() % i == 0)
      {
        result = curr->val;
      }
      i++;
      curr = curr->next;
    }
    return result;
  }
};

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Reservoir Sampling (for unknown/streaming data)

    Reservoir Sampling is an algorithm for randomly selecting k items
    from a stream of unknown length. Here k = 1.

    Algorithm:
      - Start with the first element as the chosen one.
      - For the i-th element (1-indexed), replace the chosen element
        with probability 1/i.

    Why it works (proof by induction):
      After seeing i elements, each has probability 1/i of being chosen.
      When we see element i+1:
        - P(choose i+1) = 1/(i+1)  ✓
        - P(keep any previous element) = (1/i) * (i/(i+1)) = 1/(i+1)  ✓

    This means each element is equally likely, regardless of list length!

    This is especially useful when:
      - You don't know the length of the list in advance
      - You can only do a single pass (streaming data)

    Time Complexity:  O(n) per getRandom() call
    Space Complexity: O(1)

    SOLUTION CODE:
    class Solution {
        ListNode* head;
    public:
        Solution(ListNode* head) : head(head) {
            srand(time(0));
        }

        int getRandom() {
            ListNode* curr = head;
            int result = curr->val;
            int i = 1;
            while (curr) {
                // With probability 1/i, choose this element
                if (rand() % i == 0) {
                    result = curr->val;
                }
                i++;
                curr = curr->next;
            }
            return result;
        }
    };
*/

// -------------------- Main (Test) --------------------
int main()
{
  srand(time(0));
  int arr[] = {1, 2, 3, 4, 5};
  ListNode *head = buildList(arr, 5);

  Solution sol(head);

  cout << "5 random picks: ";
  for (int i = 0; i < 5; i++)
  {
    cout << sol.getRandom() << " ";
  }
  cout << endl;
  // Each call should return 1-5 with roughly equal probability

  freeList(head);
  return 0;
}
