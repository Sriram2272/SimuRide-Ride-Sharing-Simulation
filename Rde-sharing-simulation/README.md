# SimuRide++ — High-performance Ride-Sharing Simulation (C++)

SimuRide++ is a professional, production-oriented simulation of a ride-sharing system implemented in modern C++ (C++17). The project demonstrates advanced data structures (Linked Lists, Queues, Graphs), efficient routing (Dijkstra), and a modular architecture suitable for extension with multithreading, GUI, and distributed simulation.

Features
- LinkedList and Queue implementations optimized for O(1) dynamic operations.
- Graph representation with Dijkstra shortest-path routing.
- Dispatcher module for ride allocation, cancellation, and queue management.
- Multithreading-ready design and simple sample runner.
- Unit test for routing correctness.

System Design and Data Structures
- LinkedList: custom doubly-linked list (header `include/LinkedList.h`) used by `Queue` to provide O(1) insert/remove. Useful when you require pointer stability for nodes and predictable memory behavior.
- Queue: simple FIFO wrapper (header `include/Queue.h`) built on top of `LinkedList` to provide constant-time enqueue/dequeue for high-throughput ride request processing.
- Graph: adjacency-list weighted graph (header `include/Graph.h`) representing city map. Designed for sparse graphs typical of road networks.
- Router: Dijkstra shortest-path (`include/Router.h`, `src/Router.cpp`) with path reconstruction. Works with non-negative weights; straightforward to replace with A* by adding heuristics.

Shortest Path Algorithm
- Dijkstra is used for guaranteed shortest paths on non-negative weighted road graphs. Complexity is O((V+E) log V) with a binary heap priority queue. For large city graphs, switch to a landmark-based heuristic or A* with an admissible heuristic to improve performance.

Performance Optimizations
- O(1) enqueue/dequeue using linked lists reduces queue overhead under high request rates.
- Lazy cancellation avoids costly mid-queue removals. Cancelled riders are skipped when dequeued.
- Greedy dispatcher minimizes matching latency with low overhead; replaceable with batched matching for optimality.

Build (Windows + PowerShell)

Build (Windows + PowerShell)
1. Create a build directory:

```powershell
mkdir build; cd build
cmake ..
cmake --build . --config Release
.
```

Usage
- Run the `simuride` executable produced in the build. The sample `main.cpp` constructs a tiny map and simulates drivers and riders.

Sample Input Formats
- Map file (plain text): each line is `u v weight` where u,v are integer node IDs and weight is the travel cost. Lines starting with `#` are ignored.

Example map file (map.txt):
```
# nodeA nodeB weight
0 1 1.0
1 2 1.5
1 3 2.0
```

- Rides file (plain text): each line is `id pickup_node dropoff_node`.

Example rides file (rides.txt):
```
101 1 3
102 0 2
```

How simulation works (example run)
1. Load map via `Config::load_map_file` and build the `Graph`.
2. Create `Dispatcher` with the graph and add `Driver` and `Rider` entities.
3. Dispatcher runs `dispatch_step()` periodically to match available drivers to queued riders using shortest-path distances as the distance metric.

Complexity analysis
- Enqueue/dequeue: O(1).
- Dijkstra (per route): O((V+E) log V). A single dispatch step performing two shortest path computations will dominate cost for large graphs.

Future improvements
- Replace greedy matching with min-cost max-flow for global optimality.
- Add A* with heuristics or Contraction Hierarchies for faster routing.
- Visual GUI using SFML/Qt for map rendering.
- Persistent event logs and replay for analysis.

Tutorial: Extending SimuRide++

1) Replace Dijkstra with A* (heuristic-driven search)
- Add a heuristic function h(u, v) estimating remaining travel cost (for road networks, Euclidean distance on coordinates is common).
- Modify `Router::shortest_path` to push priority using d + h(u), and when popping handle the same relaxations. Ensure heuristic is admissible (never overestimates) to maintain optimality.

2) Replace greedy matching with min-cost matching
- Collect a batch of available drivers and pending riders periodically.
- Build a bipartite graph where cost(driver, rider) = travel_time(driver.location, rider.pickup) + trip_time(pickup, dropoff).
- Use Hungarian algorithm or reduce to min-cost max-flow to get assignments minimizing total cost. This increases average system-wide efficiency but adds computational cost.

3) Integrate OpenStreetMap (OSM) data
- Use osmium or osmnx/py route tools to extract road graph and convert to a compact node/edge CSV. Preprocess to remove degree-2 nodes and contract long chains if desired.
- Load into `Graph` via `Config::load_map_file` or implement a binary loader for faster start-up.

4) CI and Tests
- The included GitHub Actions workflow builds and runs a basic datastructure test on Linux and Windows. Expand it to run all tests and add sanitizers/coverage as needed.

5) GUI ideas
- Use SFML or Qt to draw nodes/edges and animate drivers & riders. Expose a control panel to spawn requests and pause/resume simulation.


Extending
- Add more realistic routing weights and dynamic traffic updates in `Graph`.
- Replace greedy dispatcher with a matching optimization (Hungarian or min-cost flow).
- Add persistent logging, GUI visualization, and networked clients.

License
MIT
