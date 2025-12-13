#include <emscripten.h>
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <limits>

using namespace std;

/*
JSON FORMAT:
{
  "cost": [
    [0,4,0,0],
    [4,0,8,0],
    [0,8,0,2],
    [0,0,2,0]
  ],
  "source": 0
}
*/

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_dijkstra(const char* jsonStr) {
    static string result;
    string s(jsonStr);

    int src = stoi(s.substr(s.find("source") + 9));
    vector<vector<int>> cost;

    int pos = s.find("[");
    while (true) {
        int start = s.find("[", pos + 1);
        if (start == string::npos) break;
        int end = s.find("]", start);
        string row = s.substr(start + 1, end - start - 1);

        vector<int> r;
        stringstream ss(row);
        int x;
        while (ss >> x) {
            r.push_back(x);
            ss.ignore();
        }
        cost.push_back(r);
        pos = end;
    }

    int n = cost.size();
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        for (int v = 0; v < n; v++) {
            if (cost[u][v] && dist[v] > d + cost[u][v]) {
                dist[v] = d + cost[u][v];
                pq.push({dist[v], v});
            }
        }
    }

    stringstream out;
    out << "Minimum Energy Loss Paths:\n";
    for (int i = 0; i < n; i++)
        out << "Node " << i << " -> " << dist[i] << "\n";

    result = out.str();
    return result.c_str();
}

}
