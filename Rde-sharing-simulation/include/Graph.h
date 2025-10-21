// Graph representation (adjacency list) with weighted edges
#pragma once
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include <functional>

using NodeId = int;

struct Edge { NodeId to; double weight; };

class Graph {
public:
    Graph() = default;
    void add_edge(NodeId u, NodeId v, double w, bool bidir=true) {
        adj[u].push_back({v,w});
        if (bidir) adj[v].push_back({u,w});
    }

    const std::vector<Edge>& neighbors(NodeId u) const {
        static const std::vector<Edge> empty;
        auto it = adj.find(u);
        return it==adj.end()? empty : it->second;
    }

    const std::unordered_map<NodeId, std::vector<Edge>>& adjacency() const { return adj; }

private:
    std::unordered_map<NodeId, std::vector<Edge>> adj;
};
