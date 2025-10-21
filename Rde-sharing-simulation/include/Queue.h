// Simple O(1) queue wrapper using LinkedList nodes
#pragma once
#include "LinkedList.h"

template<typename T>
class Queue {
public:
    Queue() = default;
    void enqueue(const T& v) { list.push_back(v); }
    T dequeue() {
        auto n = list.front();
        T val = n->value;
        list.remove(n);
        return val;
    }
    bool empty() const { return list.empty(); }
    size_t size() const { return list.size(); }

private:
    LinkedList<T> list;
};
