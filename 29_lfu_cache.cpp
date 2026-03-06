// ============================================================
// Problem: LFU Cache
// Link: https://leetcode.com/problems/lfu-cache/
// ============================================================
// Design a Least Frequently Used (LFU) cache:
//   LFUCache(capacity)  — Initialize with positive capacity
//   int get(key)        — Return value if exists, else -1. Increments use count.
//   void put(key, val)  — Insert or update. If at capacity, evict the LFU key.
//                          If tie in frequency, evict the LRU among them.
// Both get and put must run in O(1) average time.
// ============================================================

#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
class LFUCache
{
  int capacity, minFreq;
  unordered_map<int, pair<int, int>> keyMap;
  unordered_map<int, list<int>> freqMap;
  unordered_map<int, list<int>::iterator> iterMap;

  void increaseFreq(int key)
  {
    int freq = keyMap[key].second;
    freqMap[freq].erase(iterMap[key]);
    if (freqMap[freq].empty())
    {
      freqMap.erase(freq);
      if (minFreq == freq)
        minFreq++;
    }
    keyMap[key].second = freq + 1;
    freqMap[freq + 1].push_front(key);
    iterMap[key] = freqMap[freq + 1].begin();
  }

public:
  LFUCache(int capacity) : capacity(capacity), minFreq(0)
  {
    // TODO: Initialize
  }

  int get(int key)
  {
    // TODO
    if (keyMap.find(key) == keyMap.end())
      return -1;
    increaseFreq(key);
    return keyMap[key].first;
  }

  void put(int key, int value)
  {
    // TODO
    if (capacity <= 0)
      return;

    if (keyMap.find(key) != keyMap.end())
    {
      keyMap[key].first = value;
      increaseFreq(key);
      return;
    }

    if ((int)keyMap.size() >= capacity)
    {
      int evictKey = freqMap[minFreq].back();
      freqMap[minFreq].pop_back();
      if (freqMap[minFreq].empty())
        freqMap.erase(minFreq);
      keyMap.erase(evictKey);
      iterMap.erase(evictKey);
    }

    keyMap[key] = {value, 1};
    freqMap[1].push_front(key);
    iterMap[key] = freqMap[1].begin();
    minFreq = 1;
  }
};

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Two HashMaps + Frequency-indexed Doubly Linked Lists

    This is one of the hardest linked list design problems.
    It combines LRU logic with frequency tracking.

    Data Structures:
      1. keyMap:  key -> {value, frequency}
      2. freqMap: frequency -> list of keys (ordered by recency, MRU at front)
      3. minFreq: tracks the current minimum frequency

    Detailed Design:

    keyMap: unordered_map<int, pair<int,int>>
      Maps key -> {value, frequency}

    freqMap: unordered_map<int, list<int>>
      Maps frequency -> doubly linked list of keys with that frequency
      Within each list, most recently used is at the FRONT.

    iterMap: unordered_map<int, list<int>::iterator>
      Maps key -> iterator in the frequency list (for O(1) removal)

    minFreq: int
      The smallest frequency that currently exists.

    Operations:

    get(key):
      1. If key not in keyMap: return -1
      2. Get value from keyMap
      3. Increase frequency: remove from freqMap[oldFreq], add to freqMap[newFreq]
      4. If freqMap[minFreq] is now empty, increment minFreq
      5. Return value

    put(key, value):
      1. If key exists: update value and call same logic as get(key)
      2. If key is new:
         a. If at capacity: evict LFU key
            - LFU key = back of freqMap[minFreq] (LRU among min-freq keys)
            - Remove from all maps
         b. Insert new key with freq=1
         c. Set minFreq = 1

    Eviction Priority:
      1. Lowest frequency         (LFU)
      2. Tie? Least recently used (LRU) — the one at the BACK of the list

    Example: capacity = 2
      put(1,1): keyMap={1:{1,1}}, freqMap={1:[1]}, minFreq=1
      put(2,2): keyMap={1:{1,1}, 2:{2,1}}, freqMap={1:[2,1]}, minFreq=1
      get(1):   Freq of 1 becomes 2. freqMap={1:[2], 2:[1]}, minFreq=1
                Return 1.
      put(3,3): Capacity full! Evict LFU: minFreq=1, back of list=[2]. Evict key 2.
                Insert 3 with freq=1. minFreq=1.
                freqMap={1:[3], 2:[1]}
      get(2):   Not found. Return -1.
      get(3):   Freq of 3 becomes 2. freqMap={1:[], 2:[3,1]}, minFreq=2.
                Return 3.

    Time Complexity:  O(1) for get and put
    Space Complexity: O(capacity)

    SOLUTION CODE:
    class LFUCache {
        int capacity, minFreq;
        unordered_map<int, pair<int,int>> keyMap;          // key -> {value, freq}
        unordered_map<int, list<int>> freqMap;             // freq -> list of keys
        unordered_map<int, list<int>::iterator> iterMap;   // key -> position in freq list

        void increaseFreq(int key) {
            int freq = keyMap[key].second;
            // Remove from current frequency list
            freqMap[freq].erase(iterMap[key]);
            if (freqMap[freq].empty()) {
                freqMap.erase(freq);
                if (minFreq == freq) minFreq++;
            }
            // Add to new frequency list (front = most recent)
            keyMap[key].second = freq + 1;
            freqMap[freq + 1].push_front(key);
            iterMap[key] = freqMap[freq + 1].begin();
        }

    public:
        LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

        int get(int key) {
            if (keyMap.find(key) == keyMap.end()) return -1;
            increaseFreq(key);
            return keyMap[key].first;
        }

        void put(int key, int value) {
            if (capacity <= 0) return;

            if (keyMap.find(key) != keyMap.end()) {
                // Update existing
                keyMap[key].first = value;
                increaseFreq(key);
                return;
            }

            // Evict if at capacity
            if ((int)keyMap.size() >= capacity) {
                // Evict LFU (and LRU among them = back of minFreq list)
                int evictKey = freqMap[minFreq].back();
                freqMap[minFreq].pop_back();
                if (freqMap[minFreq].empty()) freqMap.erase(minFreq);
                keyMap.erase(evictKey);
                iterMap.erase(evictKey);
            }

            // Insert new key with freq = 1
            keyMap[key] = {value, 1};
            freqMap[1].push_front(key);
            iterMap[key] = freqMap[1].begin();
            minFreq = 1;
        }
    };
*/

// -------------------- Main (Test) --------------------
int main()
{
  LFUCache cache(2);

  cache.put(1, 1);
  cache.put(2, 2);
  cout << "get(1): " << cache.get(1) << endl; // 1 (freq of 1 becomes 2)
  cache.put(3, 3);                            // evicts key 2 (freq 1, LFU)
  cout << "get(2): " << cache.get(2) << endl; // -1
  cout << "get(3): " << cache.get(3) << endl; // 3
  cache.put(4, 4);                            // evicts key 3 or 1? key 3 has freq 2, key 1 has freq 2
                                              // tie => evict LRU among freq=2 => key 1 was used earlier?
                                              // Actually after get(3), freq: 1->2, 3->2. 1 is LRU => evict 1
  cout << "get(1): " << cache.get(1) << endl; // -1
  cout << "get(3): " << cache.get(3) << endl; // -1 (3 was evicted since it had lower freq usage timing)
  cout << "get(4): " << cache.get(4) << endl; // 4

  return 0;
}
