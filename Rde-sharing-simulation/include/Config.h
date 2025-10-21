// Configuration and simple parser for sample inputs
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <tuple>

struct MapEdge { int u; int v; double w; };
struct RideReq { int id; int pickup; int dropoff; };

inline bool load_map_file(const std::string& path, std::vector<MapEdge>& out) {
    std::ifstream ifs(path);
    if (!ifs) return false;
    std::string line;
    while (std::getline(ifs,line)) {
        if (line.empty() || line[0]=='#') continue;
        std::istringstream ss(line);
        int u,v; double w;
        if (!(ss>>u>>v>>w)) continue;
        out.push_back({u,v,w});
    }
    return true;
}

inline bool load_rides_file(const std::string& path, std::vector<RideReq>& out) {
    std::ifstream ifs(path);
    if (!ifs) return false;
    std::string line;
    while (std::getline(ifs,line)) {
        if (line.empty() || line[0]=='#') continue;
        std::istringstream ss(line);
        int id,p,d;
        if (!(ss>>id>>p>>d)) continue;
        out.push_back({id,p,d});
    }
    return true;
}
