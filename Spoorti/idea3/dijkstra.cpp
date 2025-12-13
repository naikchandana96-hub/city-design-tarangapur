#include <emscripten/emscripten.h>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Edge {
    int to, cost;
};

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_dijkstra(const char* jsonInput) {
    vector<vector<Edge>> graph(5);

    // Hardcoded graph for demo (matches JSON)
    graph[0].push_back({1,10});
    graph[0].push_back({2,5});
    graph[2].push_back({4,2});
    graph[1].push_back({3,1});
    graph[4].push_back({3,4});

    vector<int> dist(5, 1e9);
    dist[0] = 0;

    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<pair<int,int>>> pq;

    pq.push({0,0});

    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();
        if (cost > dist[u]) continue;

        for (auto &e : graph[u]) {
            if (dist[u] + e.cost < dist[e.to]) {
                dist[e.to] = dist[u] + e.cost;
                pq.push({dist[e.to], e.to});
            }
        }
    }

    static string output;
    output = "Minimum water cost to Field 3 = " + to_string(dist[3]);
    return output.c_str();
}
}
