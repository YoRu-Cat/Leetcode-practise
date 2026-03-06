// ============================================================
// Problem: Design HashMap
// Link: https://leetcode.com/problems/design-hashmap/
// ============================================================
// Design a HashMap without using any built-in hash table libraries.
// Implement:
//   void put(key, value) — Insert or update key-value pair
//   int get(key)         — Return value, or -1 if key doesn't exist
//   void remove(key)     — Remove key
// Keys: 0 <= key <= 10^6, Values: 0 <= value <= 10^6
// ============================================================

#include <iostream>
#include <vector>
#include <list>
using namespace std;

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
class MyHashMap
{
  static const int SIZE = 10007;
  vector<list<pair<int, int>>> buckets;

  int hash(int key) { return key % SIZE; }

public:
  MyHashMap() : buckets(SIZE)
  {
    // TODO: Initialize
  }

  void put(int key, int value)
  {
    // TODO
    int idx = hash(key);
    for (auto &p : buckets[idx])
    {
      if (p.first == key)
      {
        p.second = value;
        return;
      }
    }
    buckets[idx].push_back({key, value});
  }

  int get(int key)
  {
    // TODO
    int idx = hash(key);
    for (auto &p : buckets[idx])
    {
      if (p.first == key)
        return p.second;
    }
    return -1;
  }

  void remove(int key)
  {
    // TODO
    int idx = hash(key);
    buckets[idx].remove_if([key](const pair<int, int> &p)
                           { return p.first == key; });
  }
};

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Array of Linked Lists (Chaining) with Key-Value Pairs

    Same concept as HashSet, but each bucket stores pairs {key, value}.

    Hash function: key % bucketSize (prime number like 10007).

    Operations:
      put(key, val): Hash key, search bucket. If found, update value.
                     If not found, insert new pair.
      get(key):      Hash key, search bucket. Return value or -1.
      remove(key):   Hash key, search bucket. Remove if found.

    Why linked list for buckets?
      - Handles collisions (multiple keys hashing to same index)
      - Dynamic size per bucket (no wasted space)
      - O(1) insert/delete within bucket

    Time Complexity:  O(n/k) average per operation
    Space Complexity: O(k + n)

    SOLUTION CODE:
    class MyHashMap {
        static const int SIZE = 10007;
        vector<list<pair<int,int>>> buckets;

        int hash(int key) { return key % SIZE; }

    public:
        MyHashMap() : buckets(SIZE) {}

        void put(int key, int value) {
            int idx = hash(key);
            for (auto& p : buckets[idx]) {
                if (p.first == key) {
                    p.second = value; // update
                    return;
                }
            }
            buckets[idx].push_back({key, value}); // insert
        }

        int get(int key) {
            int idx = hash(key);
            for (auto& p : buckets[idx]) {
                if (p.first == key) return p.second;
            }
            return -1;
        }

        void remove(int key) {
            int idx = hash(key);
            buckets[idx].remove_if([key](const pair<int,int>& p) {
                return p.first == key;
            });
        }
    };
*/

// -------------------- Main (Test) --------------------
int main()
{
  MyHashMap hm;
  hm.put(1, 1);
  hm.put(2, 2);
  cout << "get(1): " << hm.get(1) << endl; // 1
  cout << "get(3): " << hm.get(3) << endl; // -1
  hm.put(2, 1);                            // update key 2
  cout << "get(2): " << hm.get(2) << endl; // 1
  hm.remove(2);
  cout << "get(2): " << hm.get(2) << endl; // -1
  return 0;
}
