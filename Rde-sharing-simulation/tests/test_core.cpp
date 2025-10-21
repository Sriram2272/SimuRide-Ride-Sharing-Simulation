#include "Graph.h"
#include "Router.h"
#include <cassert>
#include <iostream>

int main() {
    Graph g;
    g.add_edge(0,1,1.0);
    g.add_edge(1,2,2.0);
    g.add_edge(0,2,5.0);
    Router r(g);
    auto res = r.shortest_path(0,2);
    std::cout << "dist=" << res.first << "\n";
    assert(res.first == 3.0);
    return 0;
}
