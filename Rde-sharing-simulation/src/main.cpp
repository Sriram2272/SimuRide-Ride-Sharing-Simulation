#include "Dispatcher.h"
#include "Graph.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    Graph g;
    // sample map: 0--1--2 and 1--3
    g.add_edge(0,1,1.0);
    g.add_edge(1,2,1.5);
    g.add_edge(1,3,2.0);

    Dispatcher disp(g);
    // add drivers
    disp.add_driver({1, 0, true});
    disp.add_driver({2, 2, true});

    // create and start dispatch loop
    DispatchLoop loop(disp);
    loop.start(std::chrono::milliseconds(200));

    // concurrently add riders
    using namespace std::chrono_literals;
    disp.add_rider({101, 1, 3, std::chrono::steady_clock::now()});
    std::this_thread::sleep_for(100ms);
    disp.add_rider({102, 0, 2, std::chrono::steady_clock::now()});

    // simulate a cancellation
    std::this_thread::sleep_for(300ms);
    disp.cancel_rider(102);

    // give the loop some time to dispatch
    std::this_thread::sleep_for(1s);
    loop.stop();

    return 0;
}
