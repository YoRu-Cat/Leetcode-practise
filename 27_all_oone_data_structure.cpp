// ============================================================
// Problem: All O'one Data Structure
// Link: https://leetcode.com/problems/all-oone-data-structure/
// ============================================================
// Design a data structure to store string counts with:
//   inc(key) — Increment count of key by 1 (new keys start at 1)
//   dec(key) — Decrement count of key by 1 (remove if count becomes 0)
//   getMaxKey() — Return a key with the maximum count (empty string if empty)
//   getMinKey() — Return a key with the minimum count (empty string if empty)
// ALL operations must be O(1) time.
// ============================================================

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>
using namespace std;

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
class AllOne
{
  struct Bucket
  {
    int count;
    unordered_set<string> keys;
  };

  list<Bucket> buckets;
  unordered_map<string, list<Bucket>::iterator> keyMap;

public:
  AllOne()
  {
    // TODO: Initialize
  }

  void inc(string key)
  {
    // TODO
    if (keyMap.find(key) == keyMap.end())
    {
      if (buckets.empty() || buckets.front().count != 1)
      {
        buckets.push_front({1, {}});
      }
      buckets.front().keys.insert(key);
      keyMap[key] = buckets.begin();
    }
    else
    {
      auto curBucket = keyMap[key];
      int newCount = curBucket->count + 1;
      auto nextBucket = next(curBucket);

      if (nextBucket == buckets.end() || nextBucket->count != newCount)
      {
        nextBucket = buckets.insert(nextBucket, {newCount, {}});
      }
      nextBucket->keys.insert(key);
      keyMap[key] = nextBucket;

      curBucket->keys.erase(key);
      if (curBucket->keys.empty())
        buckets.erase(curBucket);
    }
  }

  void dec(string key)
  {
    // TODO
    auto curBucket = keyMap[key];
    int newCount = curBucket->count - 1;

    if (newCount == 0)
    {
      keyMap.erase(key);
    }
    else
    {
      auto prevBucket = curBucket;
      if (curBucket != buckets.begin())
      {
        prevBucket = prev(curBucket);
      }
      if (curBucket == buckets.begin() || prevBucket->count != newCount)
      {
        prevBucket = buckets.insert(curBucket, {newCount, {}});
      }
      prevBucket->keys.insert(key);
      keyMap[key] = prevBucket;
    }

    curBucket->keys.erase(key);
    if (curBucket->keys.empty())
      buckets.erase(curBucket);
  }

  string getMaxKey()
  {
    // TODO
    return buckets.empty() ? "" : *(buckets.back().keys.begin());
  }

  string getMinKey()
  {
    // TODO
    return buckets.empty() ? "" : *(buckets.front().keys.begin());
  }
};

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Doubly Linked List of Buckets + HashMap

    This is a classic design problem requiring O(1) for all four operations.

    Data Structures:
      1. A doubly linked list of "Bucket" nodes, each storing:
         - count: the frequency value
         - keys: a set of all keys with that frequency
      2. A hash map: key -> iterator pointing to the bucket node

    The doubly linked list is kept SORTED by count (ascending).
    - Front (head->next) = minimum count bucket
    - Back (tail->prev)  = maximum count bucket

    Operations:

    inc(key):
      - If key is new: insert into bucket with count=1 (create if needed, right after head)
      - If key exists at bucket with count=c:
        - Move to bucket with count=c+1 (create if needed, right after current bucket)
        - Remove from current bucket (delete bucket if empty)

    dec(key):
      - Key is at bucket count=c:
        - If c==1: remove key entirely
        - Else: move to bucket count=c-1 (create if needed, right before current bucket)
        - Remove from current bucket (delete bucket if empty)

    getMaxKey(): return any key from tail->prev bucket  (O(1))
    getMinKey(): return any key from head->next bucket   (O(1))

    Why O(1)?
      - HashMap gives O(1) lookup of which bucket a key is in
      - Moving between adjacent buckets is O(1)
      - Inserting/removing from a set within a bucket is O(1) (unordered_set)
      - Min/Max is always at the ends of the sorted list

    Time Complexity:  O(1) for ALL operations
    Space Complexity: O(n) where n = number of unique keys

    SOLUTION CODE:
    class AllOne {
        struct Bucket {
            int count;
            unordered_set<string> keys;
        };

        list<Bucket> buckets; // doubly linked list, sorted by count
        unordered_map<string, list<Bucket>::iterator> keyMap; // key -> bucket iterator

    public:
        AllOne() {}

        void inc(string key) {
            if (keyMap.find(key) == keyMap.end()) {
                // New key — insert into count=1 bucket
                if (buckets.empty() || buckets.front().count != 1) {
                    buckets.push_front({1, {}});
                }
                buckets.front().keys.insert(key);
                keyMap[key] = buckets.begin();
            } else {
                // Existing key — move to next bucket (count+1)
                auto curBucket = keyMap[key];
                int newCount = curBucket->count + 1;
                auto nextBucket = next(curBucket);

                if (nextBucket == buckets.end() || nextBucket->count != newCount) {
                    nextBucket = buckets.insert(nextBucket, {newCount, {}});
                }
                nextBucket->keys.insert(key);
                keyMap[key] = nextBucket;

                // Remove from current bucket
                curBucket->keys.erase(key);
                if (curBucket->keys.empty()) buckets.erase(curBucket);
            }
        }

        void dec(string key) {
            auto curBucket = keyMap[key];
            int newCount = curBucket->count - 1;

            if (newCount == 0) {
                keyMap.erase(key);
            } else {
                auto prevBucket = curBucket;
                if (curBucket != buckets.begin()) {
                    prevBucket = prev(curBucket);
                }
                if (curBucket == buckets.begin() || prevBucket->count != newCount) {
                    prevBucket = buckets.insert(curBucket, {newCount, {}});
                }
                prevBucket->keys.insert(key);
                keyMap[key] = prevBucket;
            }

            curBucket->keys.erase(key);
            if (curBucket->keys.empty()) buckets.erase(curBucket);
        }

        string getMaxKey() {
            return buckets.empty() ? "" : *(buckets.back().keys.begin());
        }

        string getMinKey() {
            return buckets.empty() ? "" : *(buckets.front().keys.begin());
        }
    };
*/

// -------------------- Main (Test) --------------------
int main()
{
  AllOne obj;
  obj.inc("hello");
  obj.inc("hello");
  cout << "Max: " << obj.getMaxKey() << endl; // "hello"
  cout << "Min: " << obj.getMinKey() << endl; // "hello"

  obj.inc("leet");
  cout << "Max: " << obj.getMaxKey() << endl; // "hello" (count 2)
  cout << "Min: " << obj.getMinKey() << endl; // "leet"  (count 1)

  obj.inc("leet");
  obj.inc("leet");
  cout << "Max: " << obj.getMaxKey() << endl; // "leet"  (count 3)
  cout << "Min: " << obj.getMinKey() << endl; // "hello" (count 2)

  obj.dec("leet");
  obj.dec("leet");
  cout << "Max: " << obj.getMaxKey() << endl; // "hello" (count 2)

  return 0;
}
