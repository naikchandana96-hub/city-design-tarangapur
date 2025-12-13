#include <emscripten/emscripten.h>
#include <string>
#include <vector>
#include <queue>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_bfs(const char* input) {
    static string output;
    output.clear();

    json j = json::parse(input);
    json zones_json = j["zones"];

    int n = zones_json.size();
    vector<vector<int>> graph(n);
    for (auto& [key, val] : zones_json.items()) {
        int u = stoi(key);
        for (auto v : val) graph[u].push_back(v);
    }

    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;

    while(!q.empty()){
        int u = q.front(); q.pop();
        output += "Visiting Market Zone " + to_string(u) + "\n";
        for(int v : graph[u]){
            if(!visited[v]){
                visited[v] = true;
                q.push(v);
            }
        }
    }

    return output.c_str();
}
}
