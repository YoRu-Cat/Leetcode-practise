// ============================================================
// Problem: Design HashSet
// Link: https://leetcode.com/problems/design-hashset/
// ============================================================
// Design a HashSet without using any built-in hash table libraries.
// Implement:
//   void add(key)       — Insert key
//   void remove(key)    — Remove key
//   bool contains(key)  — Check if key exists
// Keys range: 0 <= key <= 10^6
// ============================================================

#include <iostream>
#include <vector>
#include <list>
using namespace std;

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
class MyHashSet
{
  static const int SIZE = 10007;
  vector<list<int>> buckets;

  int hash(int key) { return key % SIZE; }

public:
  MyHashSet() : buckets(SIZE)
  {
    // TODO: Initialize
  }

  void add(int key)
  {
    // TODO
    int idx = hash(key);
    for (int &k : buckets[idx])
    {
      if (k == key)
        return;
    }
    buckets[idx].push_back(key);
  }

  void remove(int key)
  {
    // TODO
    int idx = hash(key);
    buckets[idx].remove(key);
  }

  bool contains(int key)
  {
    // TODO
    int idx = hash(key);
    for (int &k : buckets[idx])
    {
      if (k == key)
        return true;
    }
    return false;
  }
};

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Array of Linked Lists (Chaining)

    A hash set uses a hash function to map keys to "buckets."
    Each bucket is a linked list to handle collisions (chaining).

    Components:
      - A fixed-size array of linked lists (buckets)
      - Hash function: key % bucketSize

    Choosing bucket size:
      A prime number reduces collisions. We use ~10007 buckets.

    Operations:
      add(key):     hash the key, search the bucket. If not found, add.
      remove(key):  hash the key, search the bucket. If found, remove.
      contains(key): hash the key, search the bucket.

    Example: bucketSize = 5
      add(1):  bucket[1%5=1].add(1)    => bucket[1]: [1]
      add(6):  bucket[6%5=1].add(6)    => bucket[1]: [1, 6]  (collision!)
      add(2):  bucket[2%5=2].add(2)    => bucket[2]: [2]
      contains(1): bucket[1]: search [1,6] => found ✓
      remove(1):   bucket[1]: remove 1 => bucket[1]: [6]

    Time Complexity:  O(n/k) average per operation (n=keys, k=buckets)
    Space Complexity: O(k + n)

    SOLUTION CODE:
    class MyHashSet {
        static const int SIZE = 10007;
        vector<list<int>> buckets;

        int hash(int key) { return key % SIZE; }

    public:
        MyHashSet() : buckets(SIZE) {}

        void add(int key) {
            int idx = hash(key);
            for (int& k : buckets[idx]) {
                if (k == key) return; // already exists
            }
            buckets[idx].push_back(key);
        }

        void remove(int key) {
            int idx = hash(key);
            buckets[idx].remove(key);
        }

        bool contains(int key) {
            int idx = hash(key);
            for (int& k : buckets[idx]) {
                if (k == key) return true;
            }
            return false;
        }
    };
*/

// -------------------- Main (Test) --------------------
int main()
{
  MyHashSet hs;
  hs.add(1);
  hs.add(2);
  cout << "contains(1): " << (hs.contains(1) ? "true" : "false") << endl; // true
  cout << "contains(3): " << (hs.contains(3) ? "true" : "false") << endl; // false
  hs.add(2);
  cout << "contains(2): " << (hs.contains(2) ? "true" : "false") << endl; // true
  hs.remove(2);
  cout << "contains(2): " << (hs.contains(2) ? "true" : "false") << endl; // false
  return 0;
}
