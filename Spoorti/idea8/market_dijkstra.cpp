#include <emscripten/emscripten.h>
#include <string>
#include <vector>
#include <queue>
#include <limits>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_dijkstra(const char* input) {
    static string output;
    output.clear();

    json j = json::parse(input);
    auto waterPoints = j["waterPoints"];
    auto edges = j["edges"];

    int n = waterPoints.size();
    vector<vector<int>> graph(n, vector<int>(n, 0));

    for (auto &e : edges) {
        int u = e["from"];
        int v = e["to"];
        int t = e["time"];
        graph[u][v] = t;
        graph[v][u] = t; // assuming undirected
    }

    vector<int> dist(n, numeric_limits<int>::max());
    dist[0] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0,0});

    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;

        for(int v=0; v<n; ++v){
            if(graph[u][v] && dist[v] > dist[u] + graph[u][v]){
                dist[v] = dist[u] + graph[u][v];
                pq.push({dist[v], v});
            }
        }
    }

    output += "Fastest time from Dock 0:\n";
    for(int i=0; i<n; ++i){
        output += waterPoints[i].get<string>() + ": " + to_string(dist[i]) + " minutes\n";
    }

    return output.c_str();
}
}
