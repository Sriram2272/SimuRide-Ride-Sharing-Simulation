#include "Dispatcher.h"
#include <chrono>

void Dispatcher::add_driver(const Driver& d) {
    std::lock_guard<std::mutex> lk(mtx);
    drivers[d.id] = d;
}

void Dispatcher::add_rider(const Rider& r) {
    std::lock_guard<std::mutex> lk(mtx);
    active_riders[r.id] = r;
    rider_queue.enqueue(r);
}

void Dispatcher::cancel_rider(int rider_id) {
    std::lock_guard<std::mutex> lk(mtx);
    if (active_riders.erase(rider_id)) {
        cancelled_riders[rider_id] = true;
        std::cout << "Rider " << rider_id << " cancelled.\n";
    }
}

void Dispatcher::dispatch_step() {
    std::lock_guard<std::mutex> lk(mtx);
    // Simple greedy: for each available driver, pop a rider and assign
    for (auto& [did, drv] : drivers) {
        if (!drv.available) continue;
        if (rider_queue.empty()) break;
    Rider r = rider_queue.dequeue();
    // lazy skip if cancelled
    if (cancelled_riders.count(r.id)) continue;
    // check if rider still active
    if (!active_riders.count(r.id)) continue;
        // compute shortest path from driver location to pickup
        auto route_to_pick = router.shortest_path(drv.location_node, r.pickup_node);
        auto route_trip = router.shortest_path(r.pickup_node, r.dropoff_node);
        std::cout << "Assigned Rider " << r.id << " to Driver " << drv.id
                  << " dist_to_pickup=" << route_to_pick.first
                  << " trip_dist=" << route_trip.first << "\n";
        // simple: mark driver unavailable and remove rider
        drv.available = false;
        active_riders.erase(r.id);
    }
}

void Dispatcher::dispatch_batch() {
    std::lock_guard<std::mutex> lk(mtx);
    // gather available drivers
    std::vector<Driver*> avail_drivers;
    for (auto& [id, d] : drivers) if (d.available) avail_drivers.push_back(&d);
    if (avail_drivers.empty()) return;

    // gather queued riders up to number of drivers
    std::vector<Rider> riders_batch;
    while (!rider_queue.empty() && riders_batch.size() < avail_drivers.size()) {
        Rider r = rider_queue.dequeue();
        if (cancelled_riders.count(r.id)) continue;
        if (!active_riders.count(r.id)) continue;
        riders_batch.push_back(r);
    }
    if (riders_batch.empty()) return;

    int n = (int)avail_drivers.size();
    int m = (int)riders_batch.size();
    std::vector<std::vector<double>> cost(n, std::vector<double>(m, 0.0));
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            auto dtopick = router.shortest_path(avail_drivers[i]->location_node, riders_batch[j].pickup_node);
            auto trip = router.shortest_path(riders_batch[j].pickup_node, riders_batch[j].dropoff_node);
            double c = dtopick.first + trip.first;
            cost[i][j] = c;
        }
    }

    auto assign = hungarian(cost);
    for (int i=0;i<n;i++){
        int j = (i < (int)assign.size()) ? assign[i] : -1;
        if (j>=0 && j<m) {
            Driver* drv = avail_drivers[i];
            Rider r = riders_batch[j];
            std::cout << "[BATCH] Assigned Rider " << r.id << " to Driver " << drv->id << " cost=" << cost[i][j] << "\n";
            drv->available = false;
            active_riders.erase(r.id);
        }
    }
}
