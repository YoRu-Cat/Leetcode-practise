// ============================================================
// Problem: Intersection of Two Linked Lists
// Link: https://leetcode.com/problems/intersection-of-two-linked-lists/
// ============================================================
// Given the heads of two singly linked lists headA and headB,
// return the node at which the two lists intersect.
// If the two linked lists have no intersection, return null.
// The linked lists must retain their original structure after the function returns.
// ============================================================

#include <iostream>
using namespace std;

// -------------------- Boilerplate --------------------
struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

// Helper: Build an intersecting pair of lists
// Returns {headA, headB} where they intersect at a common tail
void buildIntersection(ListNode *&headA, ListNode *&headB)
{
  // Common part: 8 -> 4 -> 5
  ListNode *common = new ListNode(8);
  common->next = new ListNode(4);
  common->next->next = new ListNode(5);

  // List A: 4 -> 1 -> [8 -> 4 -> 5]
  headA = new ListNode(4);
  headA->next = new ListNode(1);
  headA->next->next = common;

  // List B: 5 -> 6 -> 1 -> [8 -> 4 -> 5]
  headB = new ListNode(5);
  headB->next = new ListNode(6);
  headB->next->next = new ListNode(1);
  headB->next->next->next = common;
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

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
  ListNode *ptrA = headA;
  ListNode *ptrB = headB;
  while (ptrA != ptrB)
  {
    ptrA = ptrA ? ptrA->next : headB;
    ptrB = ptrB ? ptrB->next : headA;
  }
  return ptrA;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Two Pointer Technique

    The key insight: if two lists have different lengths before the
    intersection point, we can "equalize" them by having each pointer
    switch to the other list's head when it reaches the end.

    Pointer A travels: listA + listB
    Pointer B travels: listB + listA

    Both travel the SAME total distance, so they align at the
    intersection point (or both become null if no intersection).

    Why it works:
      lenA_unique + common + lenB_unique = lenB_unique + common + lenA_unique
      After switching, both pointers are the same distance from the intersection.

    Example:
      A: 4 -> 1 -> 8 -> 4 -> 5  (length 5)
      B: 5 -> 6 -> 1 -> 8 -> 4 -> 5  (length 6)
      After ptrA reaches end, it goes to headB.
      After ptrB reaches end, it goes to headA.
      They meet at node 8.

    Time Complexity:  O(m + n)
    Space Complexity: O(1)

    SOLUTION CODE:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* ptrA = headA;
        ListNode* ptrB = headB;
        while (ptrA != ptrB) {
            ptrA = ptrA ? ptrA->next : headB;
            ptrB = ptrB ? ptrB->next : headA;
        }
        return ptrA; // either the intersection node or nullptr
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  ListNode *headA = nullptr;
  ListNode *headB = nullptr;
  buildIntersection(headA, headB);

  cout << "List A: ";
  printList(headA);
  cout << "List B: ";
  printList(headB);

  ListNode *intersection = getIntersectionNode(headA, headB);
  if (intersection)
    cout << "Intersection at node with value: " << intersection->val << endl;
  else
    cout << "No intersection" << endl;
  // Expected: Intersection at node with value: 8

  return 0;
}
