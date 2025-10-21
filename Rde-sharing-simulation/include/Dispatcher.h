// Dispatcher: assigns drivers to riders, handles cancellations, queues
#pragma once
#include "Entities.h"
#include "Queue.h"
#include "Router.h"
#include <unordered_map>
#include <mutex>
#include <optional>
#include <iostream>
#include "Hungarian.h"

class Dispatcher {
public:
    Dispatcher(Graph& g): router(g), graph(g) {}

    void add_driver(const Driver& d);
    void add_rider(const Rider& r);
    void cancel_rider(int rider_id);

    // run one dispatch step matching available drivers to queued riders
    void dispatch_step();
    // batch matching: collect available drivers and queued riders and match with Hungarian
    void dispatch_batch();

private:
    Graph& graph;
    Router router;
    std::unordered_map<int, Driver> drivers;
    std::unordered_map<int, Rider> active_riders;
    Queue<Rider> rider_queue;
    // cancellations tracked to allow lazy removal from queue
    std::unordered_map<int, bool> cancelled_riders;
    std::mutex mtx;
};
