#include <emscripten.h>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_dijkstra(const char* jsonStr) {
    static string result;
    stringstream ss;

    json j = json::parse(jsonStr);
    int n = j["nodes"];
    auto edges = j["edges"];

    vector<vector<pair<int,int>>> graph(n);

    for (auto& e : edges) {
        graph[e["u"]].push_back({e["v"], e["w"]});
        graph[e["v"]].push_back({e["u"], e["w"]});
    }

    vector<int> dist(n, 1e9);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;

            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    ss << "Eco-Friendly Shortest Paths from Source:\n";
    for (int i = 0; i < n; i++) {
        ss << "Node " << i << " → Cost " << dist[i] << "\n";
    }

    result = ss.str();
    return result.c_str();
}

}
