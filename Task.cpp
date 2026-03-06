#include <iostream>
using namespace std;

template <typename T>
class DoublyLinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
        Node(T d)
        {
            data = d;
            next = NULL;
            prev = NULL;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    ~DoublyLinkedList()
    {
        Node* cur = head;
        while (cur)
        {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = NULL;
        tail = NULL;
    }

    bool isEmpty()
    {
        return head == NULL;
    }

    void insertAtStart(T val)
    {
        Node* node = new Node(val);
        if (isEmpty())
        {
            head = node;
            tail = node;
        }
        else
        {
            node->next = head;
            head->prev = node;
            head = node;
        }
    }

    void insertAtEnd(T val)
    {
        Node* node = new Node(val);
        if (isEmpty())
        {
            head = node;
            tail = node;
        }
        else
        {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
    }

    void insertBefore(T v1, T v2)
    {
        for (Iterator it = begin(); it != end(); ++it)
        {
            if (*it == v2)
            {
                Node* target = it.getNode();
                Node* node = new Node(v1);
                Node* prev = target->prev;
                node->next = target;
                node->prev = prev;
                target->prev = node;
                if (prev)
                    prev->next = node;
                else
                    head = node;
                return;
            }
        }
        cout << "Value " << v2 << " not found.\n";
    }

    void print()
    {
        for (Iterator it = begin(); it != end(); ++it)
        {
            cout << *it;
            if (it.getNode()->next)
                cout << " <-> ";
        }
        cout << "\n";
    }

    void deleteAtStart()
    {
        if (isEmpty()) return;
        Node* old = head;
        head = head->next;
        if (head)
            head->prev = NULL;
        else
            tail = NULL;
        delete old;
    }

    void removeDuplicates()
    {
        Node* outer = head;
        while (outer)
        {
            Node* inner = outer->next;
            while (inner)
            {
                Node* nxt = inner->next;
                if (inner->data == outer->data)
                {
                    if (inner->prev)
                        inner->prev->next = inner->next;
                    if (inner->next)
                        inner->next->prev = inner->prev;
                    if (inner == tail)
                        tail = inner->prev;
                    delete inner;
                }
                inner = nxt;
            }
            outer = outer->next;
        }
    }

    bool swapAdjacent(T value)
    {
        for (Iterator it = begin(); it != end(); ++it)
        {
            if (*it == value)
            {
                Node* a = it.getNode();
                Node* b = a->next;
                if (!b) return false;

                Node* prevA = a->prev;
                Node* nextB = b->next;

                if (prevA) prevA->next = b;
                else       head = b;
                if (nextB) nextB->prev = a;
                else       tail = a;

                b->prev = prevA;
                b->next = a;
                a->prev = b;
                a->next = nextB;

                return true;
            }
        }
        return false;
    }

    void deleteAll(T value)
    {
        Iterator it = begin();
        while (it != end())
        {
            Iterator next_it = it;
            ++next_it;
            if (*it == value)
            {
                Node* node = it.getNode();
                if (node->prev)
                    node->prev->next = node->next;
                else
                    head = node->next;
                if (node->next)
                    node->next->prev = node->prev;
                else
                    tail = node->prev;
                delete node;
            }
            it = next_it;
        }
    }

    T middle()
    {
        Iterator slow = begin();
        Iterator fast = begin();
        while (fast != end())
        {
            ++fast;
            if (fast != end())
            {
                ++fast;
                ++slow;
            }
        }
        return *slow;
    }

    bool isPalindrome()
    {
        Node* f = head;
        Node* b = tail;
        while (f != b && f->prev != b)
        {
            if (f->data != b->data) return false;
            f = f->next;
            b = b->prev;
        }
        return f->data == b->data;
    }

    class Iterator
    {
        Node* current;
    public:
        Iterator(Node* node)
        {
            current = node;
        }

        T& operator*()
        {
            return current->data;
        }

        Iterator& operator++()
        {
            if (current)
                current = current->next;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            if (current)
                current = current->next;
            return tmp;
        }

        Iterator& operator--()
        {
            if (current)
                current = current->prev;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator tmp = *this;
            if (current)
                current = current->prev;
            return tmp;
        }

        bool operator==(const Iterator& other) const
        {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const
        {
            return current != other.current;
        }

        Node* getNode() const
        {
            return current;
        }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(NULL); }
    Iterator rbegin() { return Iterator(tail); }
    Iterator rend() { return Iterator(NULL); }
};

int main()
{
    DoublyLinkedList<int> list;
    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(3);
    list.insertAtEnd(4);
    cout << "Initial:          "; list.print();

    list.insertAtStart(0);
    cout << "insertAtStart(0): "; list.print();

    list.insertBefore(99, 3);
    cout << "insertBefore(99,3): "; list.print();

    list.deleteAtStart();
    cout << "deleteAtStart:    "; list.print();

    cout << "isEmpty: " << (list.isEmpty() ? "true" : "false") << "\n";

    cout << "\nremoveDuplicates:\n";
    DoublyLinkedList<int> dup;
    for (int v : {1, 2, 2, 3, 1}) dup.insertAtEnd(v);
    cout << "Input:  "; dup.print();
    dup.removeDuplicates();
    cout << "Output: "; dup.print();

    cout << "\nswapAdjacent(20):\n";
    DoublyLinkedList<int> sw;
    for (int v : {10, 20, 30, 40}) sw.insertAtEnd(v);
    cout << "Input:  "; sw.print();
    sw.swapAdjacent(20);
    cout << "Output: "; sw.print();

    cout << "\ndeleteAll(1):\n";
    DoublyLinkedList<int> da;
    for (int v : {1, 2, 1, 3, 1}) da.insertAtEnd(v);
    cout << "Input:  "; da.print();
    da.deleteAll(1);
    cout << "Output: "; da.print();

    cout << "\nmiddle:\n";
    DoublyLinkedList<int> mid;
    for (int v : {1, 2, 3, 4, 5}) mid.insertAtEnd(v);
    cout << "List:   "; mid.print();
    cout << "Middle: " << mid.middle() << "\n";

    cout << "\nisPalindrome:\n";
    DoublyLinkedList<int> pal;
    for (int v : {1, 2, 3, 2, 1}) pal.insertAtEnd(v);
    cout << "Input:  "; pal.print();
    cout << "Output: " << (pal.isPalindrome() ? "Yes" : "No") << "\n";

    DoublyLinkedList<int> np;
    for (int v : {1, 2, 3, 4, 5}) np.insertAtEnd(v);
    cout << "Input:  "; np.print();
    cout << "Output: " << (np.isPalindrome() ? "Yes" : "No") << "\n";

    cout << "\nIterator forward:  ";
    DoublyLinkedList<int> itr;
    for (int v : {10, 20, 30, 40, 50}) itr.insertAtEnd(v);
    for (DoublyLinkedList<int>::Iterator it = itr.begin(); it != itr.end(); ++it)
    {
        cout << *it;
        if (it.getNode()->next) cout << " <-> ";
    }
    cout << "\n";

    cout << "Iterator reverse:  ";
    for (DoublyLinkedList<int>::Iterator it = itr.rbegin(); it != itr.rend(); --it)
    {
        cout << *it;
        if (it.getNode()->prev) cout << " <-> ";
    }
    cout << "\n";

    return 0;
}