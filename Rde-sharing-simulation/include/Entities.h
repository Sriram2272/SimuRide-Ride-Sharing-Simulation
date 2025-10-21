// Rider and Driver entities
#pragma once
#include <string>
#include <chrono>

using TimePoint = std::chrono::steady_clock::time_point;

struct Rider {
    int id;
    int pickup_node;
    int dropoff_node;
    TimePoint request_time;
};

struct Driver {
    int id;
    int location_node;
    bool available = true;
};
