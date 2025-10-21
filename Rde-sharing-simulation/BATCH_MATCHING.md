Batched matching (Hungarian)

This project includes an implementation of the Hungarian algorithm in `include/Hungarian.h`. The dispatcher exposes `Dispatcher::dispatch_batch()` which:

1. Collects available drivers
2. Dequeues up to that number of riders (skips cancelled riders)
3. Builds a cost matrix where cost[i][j] = distance(driver_i -> rider_j.pickup) + distance(pickup -> dropoff)
4. Calls the Hungarian matcher to compute assignments minimizing total cost
5. Assigns matched pairs and marks drivers unavailable

Complexity notes:
- Constructing cost matrix: O(d * r * (Dijkstra cost)) where d = drivers, r = riders in the batch.
- Hungarian algorithm runtime: O(n^3) where n = max(d, r) after padding.

This approach improves global efficiency at the cost of additional computation compared to the greedy dispatcher. It's appropriate when batching (e.g., 10-100 drivers) and when per-dispatch latency can tolerate the added compute.
