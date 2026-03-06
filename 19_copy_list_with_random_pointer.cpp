// ============================================================
// Problem: Copy List with Random Pointer
// Link: https://leetcode.com/problems/copy-list-with-random-pointer/
// ============================================================
// A linked list has nodes with an additional `random` pointer
// that can point to any node in the list or null.
// Construct a DEEP COPY of the list.
// ============================================================

#include <iostream>
#include <unordered_map>
using namespace std;

// -------------------- Boilerplate --------------------
struct Node
{
  int val;
  Node *next;
  Node *random;
  Node(int x) : val(x), next(nullptr), random(nullptr) {}
};

// Helper: Build a list with random pointers from arrays
// vals[i] = node value, randomIdx[i] = index of random pointer target (-1 for null)
Node *buildRandomList(int vals[], int randomIdx[], int n)
{
  if (n == 0)
    return nullptr;
  Node **nodes = new Node *[n];
  for (int i = 0; i < n; i++)
    nodes[i] = new Node(vals[i]);
  for (int i = 0; i < n - 1; i++)
    nodes[i]->next = nodes[i + 1];
  for (int i = 0; i < n; i++)
    nodes[i]->random = (randomIdx[i] >= 0) ? nodes[randomIdx[i]] : nullptr;
  Node *head = nodes[0];
  delete[] nodes;
  return head;
}

void printRandomList(Node *head)
{
  Node *curr = head;
  while (curr)
  {
    cout << "[" << curr->val << ", random=";
    if (curr->random)
      cout << curr->random->val;
    else
      cout << "null";
    cout << "] ";
    curr = curr->next;
  }
  cout << endl;
}

void freeRandomList(Node *head)
{
  while (head)
  {
    Node *t = head;
    head = head->next;
    delete t;
  }
}

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
Node *copyRandomList(Node *head)
{
  // TODO: Implement this
  if (!head)
    return nullptr;
  unordered_map<Node *, Node *> mp;

  // Pass 1: Create clones
  Node *curr = head;
  while (curr)
  {
    mp[curr] = new Node(curr->val);
    curr = curr->next;
  }

  // Pass 2: Set next and random
  curr = head;
  while (curr)
  {
    mp[curr]->next = mp[curr->next];
    mp[curr]->random = mp[curr->random];
    curr = curr->next;
  }

  return mp[head];
}

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH 1: HashMap (Easier to understand)

    Use a hash map: oldNode -> newNode (clone).
    Pass 1: Create all cloned nodes, map old to new.
    Pass 2: Set next and random pointers using the map.

    Time: O(n), Space: O(n)

    APPROACH 2: Interleaving (O(1) Space, Optimal)

    Three passes through the list:

    Pass 1 — Interleave clones:
      Insert a clone of each node right after the original.
      A -> A' -> B -> B' -> C -> C'

    Pass 2 — Set random pointers:
      For each original node, if it has a random pointer:
        clone.random = original.random.next (which is the clone of random target)

    Pass 3 — Separate the two lists:
      Extract the cloned nodes into their own list.
      Restore original list.

    Example: A(random->C) -> B(random->A) -> C(random->B)

      Pass 1: A -> A' -> B -> B' -> C -> C'
      Pass 2: A'.random = A.random.next = C.next = C'
              B'.random = B.random.next = A.next = A'
              C'.random = C.random.next = B.next = B'
      Pass 3: Separate: A' -> B' -> C' (with correct random pointers)

    Time: O(n), Space: O(1) (excluding output)

    SOLUTION CODE (HashMap approach):
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        unordered_map<Node*, Node*> mp;

        // Pass 1: Create clones
        Node* curr = head;
        while (curr) {
            mp[curr] = new Node(curr->val);
            curr = curr->next;
        }

        // Pass 2: Set next and random
        curr = head;
        while (curr) {
            mp[curr]->next = mp[curr->next];
            mp[curr]->random = mp[curr->random];
            curr = curr->next;
        }

        return mp[head];
    }

    SOLUTION CODE (Interleaving - O(1) space):
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        // Pass 1: Interleave clones
        Node* curr = head;
        while (curr) {
            Node* clone = new Node(curr->val);
            clone->next = curr->next;
            curr->next = clone;
            curr = clone->next;
        }

        // Pass 2: Set random pointers
        curr = head;
        while (curr) {
            if (curr->random)
                curr->next->random = curr->random->next;
            curr = curr->next->next;
        }

        // Pass 3: Separate lists
        Node* cloneHead = head->next;
        curr = head;
        Node* clone = cloneHead;
        while (curr) {
            curr->next = clone->next;
            curr = curr->next;
            if (curr) {
                clone->next = curr->next;
                clone = clone->next;
            }
        }
        return cloneHead;
    }
*/

// -------------------- Main (Test) --------------------
int main()
{
  int vals[] = {7, 13, 11, 10, 1};
  int randomIdx[] = {-1, 0, 4, 2, 0}; // random targets by index
  Node *head = buildRandomList(vals, randomIdx, 5);

  cout << "Original: ";
  printRandomList(head);

  Node *copy = copyRandomList(head);
  cout << "Copy:     ";
  printRandomList(copy);

  cout << "Are they different objects? " << (head != copy ? "Yes" : "No") << endl;

  freeRandomList(head);
  freeRandomList(copy);
  return 0;
}
