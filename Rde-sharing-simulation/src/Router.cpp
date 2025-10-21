#include "Router.h"
#include <queue>
#include <limits>
#include <algorithm>

std::pair<double, std::vector<NodeId>> Router::shortest_path(NodeId src, NodeId dst) const {
    const auto& adj = graph.adjacency();
    std::unordered_map<NodeId, double> dist;
    std::unordered_map<NodeId, NodeId> prev;
    struct Item { double d; NodeId u; };
    struct Cmp { bool operator()(const Item& a, const Item& b) const { return a.d > b.d; } };
    std::priority_queue<Item, std::vector<Item>, Cmp> pq;

    pq.push({0.0, src});
    dist[src] = 0.0;

    while (!pq.empty()) {
        auto it = pq.top(); pq.pop();
        double d = it.d; NodeId u = it.u;
        if (d > dist[u]) continue;
        if (u == dst) break;
        for (const auto& e : graph.neighbors(u)) {
            double nd = d + e.weight;
            if (!dist.count(e.to) || nd < dist[e.to]) {
                dist[e.to] = nd;
                prev[e.to] = u;
                pq.push({nd, e.to});
            }
        }
    }

    if (!dist.count(dst)) return {std::numeric_limits<double>::infinity(), {}};
    std::vector<NodeId> path;
    for (NodeId at = dst; ; at = prev[at]) {
        path.push_back(at);
        if (at == src) break;
    }
    std::reverse(path.begin(), path.end());
    return {dist[dst], path};
}
