#include "LinkedList.h"
#include "Queue.h"
#include <cassert>
#include <iostream>

int main_datastruct() {
    LinkedList<int> ll;
    auto n1 = ll.push_back(1);
    auto n2 = ll.push_back(2);
    assert(ll.size()==2);
    ll.remove(n1);
    assert(ll.size()==1);
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    int a = q.dequeue();
    assert(a==10);
    a = q.dequeue();
    assert(a==20);
    std::cout << "datastruct tests passed\n";
    return 0;
}
