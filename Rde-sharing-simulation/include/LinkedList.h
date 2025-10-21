// Doubly-linked list minimal implementation optimized for O(1) insert/remove
#pragma once
#include <memory>

template<typename T>
class LinkedList {
public:
    struct Node {
        T value;
        Node* prev = nullptr;
        Node* next = nullptr;
        Node(const T& v): value(v) {}
    };

    LinkedList() = default;
    ~LinkedList() { clear(); }

    Node* push_front(const T& v) {
        Node* n = new Node(v);
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = n;
        ++sz;
        return n;
    }

    Node* push_back(const T& v) {
        Node* n = new Node(v);
        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = n;
        ++sz;
        return n;
    }

    void remove(Node* n) {
        if (!n) return;
        if (n->prev) n->prev->next = n->next; else head = n->next;
        if (n->next) n->next->prev = n->prev; else tail = n->prev;
        delete n;
        --sz;
    }

    Node* front() const { return head; }
    Node* back() const { return tail; }
    bool empty() const { return sz==0; }
    size_t size() const { return sz; }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        sz = 0;
    }

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t sz = 0;
};
