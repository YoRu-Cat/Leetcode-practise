// ============================================================
// Problem: LRU Cache
// Link: https://leetcode.com/problems/lru-cache/
// ============================================================
// Design a Least Recently Used (LRU) cache:
//   LRUCache(capacity)  — Initialize with positive capacity
//   int get(key)        — Return value if key exists, else -1. Marks as recently used.
//   void put(key, val)  — Insert or update. If capacity exceeded, evict the LRU key.
// Both get and put must run in O(1) average time.
// ============================================================

#include <iostream>
#include <unordered_map>
using namespace std;

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
class LRUCache
{
  struct DLLNode
  {
    int key, val;
    DLLNode *prev, *next;
    DLLNode(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
  };

  int capacity;
  unordered_map<int, DLLNode *> map;
  DLLNode *head, *tail;

  void removeNode(DLLNode *node)
  {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void addToFront(DLLNode *node)
  {
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
  }

  void moveToFront(DLLNode *node)
  {
    removeNode(node);
    addToFront(node);
  }

public:
  LRUCache(int capacity) : capacity(capacity)
  {
    // TODO: Initialize
    head = new DLLNode(0, 0);
    tail = new DLLNode(0, 0);
    head->next = tail;
    tail->prev = head;
  }

  int get(int key)
  {
    // TODO
    if (map.find(key) == map.end())
      return -1;
    DLLNode *node = map[key];
    moveToFront(node);
    return node->val;
  }

  void put(int key, int value)
  {
    // TODO
    if (map.find(key) != map.end())
    {
      DLLNode *node = map[key];
      node->val = value;
      moveToFront(node);
    }
    else
    {
      if ((int)map.size() == capacity)
      {
        DLLNode *lru = tail->prev;
        removeNode(lru);
        map.erase(lru->key);
        delete lru;
      }
      DLLNode *newNode = new DLLNode(key, value);
      addToFront(newNode);
      map[key] = newNode;
    }
  }

  ~LRUCache()
  {
    DLLNode *curr = head;
    while (curr)
    {
      DLLNode *next = curr->next;
      delete curr;
      curr = next;
    }
  }
};

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: HashMap + Doubly Linked List

    This is a CLASSIC interview problem. The key insight:

    We need TWO things:
      1. O(1) LOOKUP by key      => HashMap
      2. O(1) INSERT/REMOVE/REORDER by recency => Doubly Linked List

    Doubly Linked List:
      - Most recently used at the FRONT (after head dummy)
      - Least recently used at the BACK (before tail dummy)
      - Using dummy head/tail simplifies edge cases

    HashMap:
      key -> pointer to the DLL node containing {key, value}

    Operations:

    get(key):
      - If key not in map: return -1
      - If key found: move node to front (most recent), return value

    put(key, value):
      - If key exists: update value, move to front
      - If key is new:
        - If at capacity: remove the tail node (LRU), erase from map
        - Create new node, add to front, add to map

    Helper functions:
      - moveToFront(node): remove from current position, insert after head
      - removeTail(): remove the node before tail, return it

    Example: capacity = 2
      put(1, 1):  DLL: [1:1], map: {1->node}
      put(2, 2):  DLL: [2:2, 1:1], map: {1->node, 2->node}
      get(1):     Move 1 to front. DLL: [1:1, 2:2]. Return 1.
      put(3, 3):  At capacity! Remove LRU (2). DLL: [3:3, 1:1], map: {1,3}
      get(2):     Not in map. Return -1.
      put(4, 4):  Remove LRU (1). DLL: [4:4, 3:3], map: {3,4}
      get(1):     Return -1
      get(3):     Move 3 to front. DLL: [3:3, 4:4]. Return 3.
      get(4):     Move 4 to front. DLL: [4:4, 3:3]. Return 4.

    Time Complexity:  O(1) for get and put
    Space Complexity: O(capacity)

    SOLUTION CODE:
    class LRUCache {
        struct DLLNode {
            int key, val;
            DLLNode *prev, *next;
            DLLNode(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
        };

        int capacity;
        unordered_map<int, DLLNode*> map;
        DLLNode *head, *tail; // dummy head and tail

        void removeNode(DLLNode* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        void addToFront(DLLNode* node) {
            node->next = head->next;
            node->prev = head;
            head->next->prev = node;
            head->next = node;
        }

        void moveToFront(DLLNode* node) {
            removeNode(node);
            addToFront(node);
        }

    public:
        LRUCache(int capacity) : capacity(capacity) {
            head = new DLLNode(0, 0);
            tail = new DLLNode(0, 0);
            head->next = tail;
            tail->prev = head;
        }

        int get(int key) {
            if (map.find(key) == map.end()) return -1;
            DLLNode* node = map[key];
            moveToFront(node);
            return node->val;
        }

        void put(int key, int value) {
            if (map.find(key) != map.end()) {
                DLLNode* node = map[key];
                node->val = value;
                moveToFront(node);
            } else {
                if ((int)map.size() == capacity) {
                    // Evict LRU (node before tail)
                    DLLNode* lru = tail->prev;
                    removeNode(lru);
                    map.erase(lru->key);
                    delete lru;
                }
                DLLNode* newNode = new DLLNode(key, value);
                addToFront(newNode);
                map[key] = newNode;
            }
        }

        ~LRUCache() {
            DLLNode* curr = head;
            while (curr) {
                DLLNode* next = curr->next;
                delete curr;
                curr = next;
            }
        }
    };
*/

// -------------------- Main (Test) --------------------
int main()
{
  LRUCache cache(2);

  cache.put(1, 1);
  cache.put(2, 2);
  cout << "get(1): " << cache.get(1) << endl; // 1
  cache.put(3, 3);                            // evicts key 2
  cout << "get(2): " << cache.get(2) << endl; // -1
  cache.put(4, 4);                            // evicts key 1
  cout << "get(1): " << cache.get(1) << endl; // -1
  cout << "get(3): " << cache.get(3) << endl; // 3
  cout << "get(4): " << cache.get(4) << endl; // 4

  return 0;
}
