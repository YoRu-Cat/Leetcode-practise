// ============================================================
// Problem: Design a Text Editor
// Link: https://leetcode.com/problems/design-a-text-editor/
// ============================================================
// Design a text editor with a cursor:
//   TextEditor()            — Initialize with empty text, cursor at position 0
//   void addText(text)      — Add text at cursor, cursor moves to end of added text
//   int deleteText(k)       — Delete k chars left of cursor, return count actually deleted
//   string cursorLeft(k)    — Move cursor left by k (or less), return last 10 chars left of cursor
//   string cursorRight(k)   — Move cursor right by k (or less), return last 10 chars left of cursor
// ============================================================

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// -------------------- Solution --------------------
// YOUR SOLUTION HERE:
class TextEditor
{
  string left, right; // right is stored in reverse

public:
  TextEditor()
  {
    // TODO: Initialize
  }

  void addText(string text)
  {
    // TODO
    left += text;
  }

  int deleteText(int k)
  {
    // TODO
    int deleted = min(k, (int)left.size());
    left.erase(left.size() - deleted);
    return deleted;
  }

  string cursorLeft(int k)
  {
    // TODO
    int moves = min(k, (int)left.size());
    for (int i = 0; i < moves; i++)
    {
      right += left.back();
      left.pop_back();
    }
    int len = min(10, (int)left.size());
    return left.substr(left.size() - len);
  }

  string cursorRight(int k)
  {
    // TODO
    int moves = min(k, (int)right.size());
    for (int i = 0; i < moves; i++)
    {
      left += right.back();
      right.pop_back();
    }
    int len = min(10, (int)left.size());
    return left.substr(left.size() - len);
  }
};

// -------------------- Solution Explained (in comments) --------------------
/*
    APPROACH: Two Stacks (Left and Right of Cursor)

    Use two stacks (or strings used as stacks):
      - `left`:  characters to the LEFT of the cursor
      - `right`: characters to the RIGHT of the cursor (in reverse)

    The cursor is implicitly between left.top() and right.top().

    Operations:
      addText(text):  push each char onto left stack
      deleteText(k):  pop min(k, left.size()) from left
      cursorLeft(k):  pop from left, push to right (k times)
      cursorRight(k): pop from right, push to left (k times)

    Why two stacks?
      - All operations happen at the cursor = top of stacks
      - O(1) per character for add/delete
      - O(k) for cursor movement

    Example: addText("leetcode"), cursor after 'e'
      left:  "leetcode"     right: ""
      Cursor: leetcode|

      cursorLeft(4):
      left:  "leet"         right: "edoc"  (reversed: "code")
      Cursor: leet|code

      deleteText(3):
      left:  "l"            right: "edoc"
      Cursor: l|code
      Deleted 3 chars

      cursorRight(2):
      left:  "lco"          right: "ed"    (take 'c','o' from right -> left)
      Cursor: lco|de

    For returning "last 10 chars left of cursor":
      Just return the last min(10, left.size()) chars of left string.

    Time: O(k) per operation where k is the parameter
    Space: O(n) total characters

    SOLUTION CODE:
    class TextEditor {
        string left, right; // right is stored in reverse
    public:
        TextEditor() {}

        void addText(string text) {
            left += text;
        }

        int deleteText(int k) {
            int deleted = min(k, (int)left.size());
            left.erase(left.size() - deleted);
            return deleted;
        }

        string cursorLeft(int k) {
            int moves = min(k, (int)left.size());
            for (int i = 0; i < moves; i++) {
                right += left.back();
                left.pop_back();
            }
            int len = min(10, (int)left.size());
            return left.substr(left.size() - len);
        }

        string cursorRight(int k) {
            int moves = min(k, (int)right.size());
            for (int i = 0; i < moves; i++) {
                left += right.back();
                right.pop_back();
            }
            int len = min(10, (int)left.size());
            return left.substr(left.size() - len);
        }
    };

    // NOTE: This can also be done with a doubly linked list where
    // each node stores a character and the cursor is a node pointer.
    // The two-stack approach is simpler and more cache-friendly.
*/

// -------------------- Main (Test) --------------------
int main()
{
  TextEditor editor;
  editor.addText("leetcode");
  cout << "deleteText(4): " << editor.deleteText(4) << endl; // 4 (deleted "code")
  editor.addText("practice");
  // Text: "leetpractice", cursor at end
  cout << "cursorLeft(3): \"" << editor.cursorLeft(3) << "\"" << endl;
  // cursor moves 3 left, now: "leetpract|ice", returns "leetpract"(last 10)
  cout << "cursorLeft(8): \"" << editor.cursorLeft(8) << "\"" << endl;
  // cursor moves 8 left, now: "l|eetpractice" wait...
  // Let me trace: "leetpract" left, "eci" right
  // Move 8 left: "l" left, "tcarptee" + "eci" right => returns "l"
  cout << "deleteText(10): " << editor.deleteText(10) << endl; // 1 (only "l" left)
  cout << "cursorLeft(2): \"" << editor.cursorLeft(2) << "\"" << endl;
  // empty left, returns ""
  cout << "cursorRight(6): \"" << editor.cursorRight(6) << "\"" << endl;
  // moves 6 right into the remaining text

  return 0;
}
