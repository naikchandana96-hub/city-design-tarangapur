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
const char* run_dijkstra(const char* input){
    static string output;
    output.clear();

    json j = json::parse(input);
    vector<vector<int>> graph = j["graph"];
    int src = j.value("source", 0);

    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, src});

    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        for(int v = 0; v < n; v++){
            if(graph[u][v] > 0 && dist[v] > dist[u] + graph[u][v]){
                dist[v] = dist[u] + graph[u][v];
                pq.push({dist[v], v});
            }
        }
    }

    for(int i = 0; i < n; i++)
        output += "Optimal price path to market " + to_string(i) + " = " + to_string(dist[i]) + "\n";

    return output.c_str();
}
}
