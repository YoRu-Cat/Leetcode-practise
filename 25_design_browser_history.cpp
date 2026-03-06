// ============================================================
// Problem: Design Browser History
// Link: https://leetcode.com/problems/design-browser-history/
// ============================================================
// Design a browser history system:
//   BrowserHistory(homepage)  — Start on the homepage
//   void visit(url)           — Visit url from current page (clears forward history)
//   string back(steps)        — Go back at most `steps` in history
//   string forward(steps)     — Go forward at most `steps` in history
// ============================================================

#include <iostream>
#include <string>
using namespace std;

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
class BrowserHistory
{
  struct PageNode
  {
    string url;
    PageNode *prev;
    PageNode *next;
    PageNode(string u) : url(u), prev(nullptr), next(nullptr) {}
  };

  PageNode *current;

public:
  BrowserHistory(string homepage)
  {
    // TODO: Initialize
    current = new PageNode(homepage);
  }

  void visit(string url)
  {
    // TODO
    PageNode *forward = current->next;
    while (forward)
    {
      PageNode *temp = forward;
      forward = forward->next;
      delete temp;
    }

    PageNode *newPage = new PageNode(url);
    current->next = newPage;
    newPage->prev = current;
    current = newPage;
  }

  string back(int steps)
  {
    // TODO
    while (steps > 0 && current->prev)
    {
      current = current->prev;
      steps--;
    }
    return current->url;
  }

  string forward(int steps)
  {
    // TODO
    while (steps > 0 && current->next)
    {
      current = current->next;
      steps--;
    }
    return current->url;
  }

  ~BrowserHistory()
  {
    while (current->prev)
      current = current->prev;
    while (current)
    {
      PageNode *temp = current;
      current = current->next;
      delete temp;
    }
  }
};

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Doubly Linked List

    Each node stores a URL and has prev/next pointers.
    A `current` pointer tracks where we are in history.

    visit(url):
      - Create new node after current
      - Discard all forward history (everything after current)
      - Move current to the new node

    back(steps):
      - Move current backward by min(steps, available_back) steps
      - Return current URL

    forward(steps):
      - Move current forward by min(steps, available_forward) steps
      - Return current URL

    Why doubly linked list?
      - O(1) insert at current position
      - O(1) discard forward history (just cut the next pointer)
      - Natural back/forward traversal with prev/next

    Example:
      BrowserHistory("google.com")
        current -> [google.com]

      visit("fb.com")
        [google.com] <-> [fb.com]
                          ^ current

      visit("youtube.com")
        [google.com] <-> [fb.com] <-> [youtube.com]
                                       ^ current

      back(1) => "fb.com"
        [google.com] <-> [fb.com] <-> [youtube.com]
                          ^ current

      visit("linkedin.com")  — clears forward history!
        [google.com] <-> [fb.com] <-> [linkedin.com]
                                       ^ current
        (youtube.com is gone)

    Time: O(1) for visit, O(steps) for back/forward
    Space: O(n) total pages visited

    SOLUTION CODE:
    struct PageNode {
        string url;
        PageNode* prev;
        PageNode* next;
        PageNode(string u) : url(u), prev(nullptr), next(nullptr) {}
    };

    class BrowserHistory {
        PageNode* current;
    public:
        BrowserHistory(string homepage) {
            current = new PageNode(homepage);
        }

        void visit(string url) {
            // Delete forward history
            PageNode* forward = current->next;
            while (forward) {
                PageNode* temp = forward;
                forward = forward->next;
                delete temp;
            }

            // Create new page and link
            PageNode* newPage = new PageNode(url);
            current->next = newPage;
            newPage->prev = current;
            current = newPage;
        }

        string back(int steps) {
            while (steps > 0 && current->prev) {
                current = current->prev;
                steps--;
            }
            return current->url;
        }

        string forward(int steps) {
            while (steps > 0 && current->next) {
                current = current->next;
                steps--;
            }
            return current->url;
        }

        ~BrowserHistory() {
            // Go to the beginning
            while (current->prev) current = current->prev;
            while (current) {
                PageNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    };
*/

// -------------------- Main (Test) --------------------
int main()
{
  BrowserHistory bh("google.com");
  bh.visit("facebook.com");
  bh.visit("youtube.com");

  cout << "back(1): " << bh.back(1) << endl;       // facebook.com
  cout << "back(1): " << bh.back(1) << endl;       // google.com
  cout << "forward(1): " << bh.forward(1) << endl; // facebook.com

  bh.visit("linkedin.com");                        // clears youtube.com from forward
  cout << "forward(2): " << bh.forward(2) << endl; // linkedin.com (can't go further)
  cout << "back(2): " << bh.back(2) << endl;       // google.com
  cout << "back(7): " << bh.back(7) << endl;       // google.com (can't go further back)

  return 0;
}
