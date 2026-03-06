// ============================================================
// Problem: Merge k Sorted Lists
// Link: https://leetcode.com/problems/merge-k-sorted-lists/
// ============================================================
// You are given an array of k sorted linked lists.
// Merge all the linked lists into one sorted linked list.
// Example: [[1,4,5],[1,3,4],[2,6]] => 1->1->2->3->4->4->5->6
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
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
ListNode *mergeKLists(vector<ListNode *> &lists)
{
  // TODO: Implement this
  auto cmp = [](ListNode *a, ListNode *b)
  {
    return a->val > b->val;
  };
  priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> pq(cmp);

  for (auto &head : lists)
  {
    if (head)
      pq.push(head);
  }

  ListNode dummy;
  ListNode *tail = &dummy;

  while (!pq.empty())
  {
    ListNode *smallest = pq.top();
    pq.pop();
    tail->next = smallest;
    tail = tail->next;
    if (smallest->next)
    {
      pq.push(smallest->next);
    }
  }

  return dummy.next;
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH 1: Min-Heap (Priority Queue)

    Use a min-heap to always pick the smallest element among
    all k list heads.

    1. Push all k list heads into the min-heap
    2. Pop the smallest, add it to result
    3. Push the next node from that list into the heap
    4. Repeat until heap is empty

    Time: O(N log k) where N = total nodes, k = number of lists
    Space: O(k) for the heap

    APPROACH 2: Divide and Conquer (Merge Sort Style)

    Pair up lists and merge each pair. Repeat until one list remains.
    Round 1: k lists => k/2 merged lists
    Round 2: k/2 => k/4
    ...until 1 list remains.

    Time: O(N log k)
    Space: O(1) extra (ignoring recursion)

    SOLUTION CODE (Min-Heap):
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Custom comparator for min-heap
        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val; // min-heap
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

        // Push all non-null heads
        for (auto& head : lists) {
            if (head) pq.push(head);
        }

        ListNode dummy;
        ListNode* tail = &dummy;

        while (!pq.empty()) {
            ListNode* smallest = pq.top();
            pq.pop();
            tail->next = smallest;
            tail = tail->next;
            if (smallest->next) {
                pq.push(smallest->next);
            }
        }

        return dummy.next;
    }

    SOLUTION CODE (Divide and Conquer):
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val <= l2->val) { tail->next = l1; l1 = l1->next; }
            else { tail->next = l2; l2 = l2->next; }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        int n = lists.size();
        while (n > 1) {
            for (int i = 0; i < n / 2; i++) {
                lists[i] = mergeTwoLists(lists[i], lists[n - 1 - i]);
            }
            n = (n + 1) / 2;
        }
        return lists[0];
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int a1[] = {1, 4, 5};
  int a2[] = {1, 3, 4};
  int a3[] = {2, 6};

  vector<ListNode *> lists;
  lists.push_back(buildList(a1, 3));
  lists.push_back(buildList(a2, 3));
  lists.push_back(buildList(a3, 2));

  cout << "Lists:" << endl;
  for (auto &l : lists)
  {
    cout << "  ";
    printList(l);
  }

  ListNode *merged = mergeKLists(lists);
  cout << "Merged: ";
  printList(merged);
  // Expected: 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6

  freeList(merged);
  return 0;
}
