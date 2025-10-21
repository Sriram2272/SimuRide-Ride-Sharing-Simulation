// Dijkstra shortest path implementation with path reconstruction
#pragma once
#include "Graph.h"
#include <vector>
#include <unordered_map>
#include <limits>

class Router {
public:
    Router(const Graph& g): graph(g) {}

    // returns pair<distance, path nodes>
    std::pair<double, std::vector<NodeId>> shortest_path(NodeId src, NodeId dst) const;

private:
    const Graph& graph;
};
