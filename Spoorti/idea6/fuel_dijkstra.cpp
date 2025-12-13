#include <emscripten.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <queue>

using namespace std;

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_dijkstra(const char* jsonStr) {
    static string result;
    string s(jsonStr);

    // Parse number of nodes
    int n = 0;
    int pos_nodes = s.find("nodes");
    if (pos_nodes != string::npos) {
        string number;
        for (size_t i = pos_nodes; i < s.size(); i++) {
            if (isdigit(s[i])) number += s[i];
            else if (!number.empty()) break;
        }
        n = stoi(number);
    }

    vector<vector<int>> graph(n, vector<int>(n, 0));

    // Parse adjacency matrix safely
    int pos = s.find("graph");
    pos = s.find("[", pos);
    for (int i = 0; i < n; i++) {
        pos = s.find("[", pos + 1);
        int end_row = s.find("]", pos);
        string row = s.substr(pos + 1, end_row - pos - 1);

        stringstream ss(row);
        string token;
        int j = 0;
        while (getline(ss, token, ',')) {
            stringstream ts(token);
            int val;
            if (ts >> val) graph[i][j++] = val;
        }

        pos = end_row;
    }

    // Dijkstra
    vector<int> dist(n, numeric_limits<int>::max());
    dist[0] = 0;
    using pii = pair<int,int>;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0,0});

    stringstream out;
    out << "Dijkstra Fuel-Efficient Routes:\n";

    while (!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && dist[v] > dist[u] + graph[u][v]) {
                dist[v] = dist[u] + graph[u][v];
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < n; i++)
        out << "Fuel to reach zone " << i << ": " << dist[i] << "\n";

    result = out.str();
    return result.c_str();
}

}
