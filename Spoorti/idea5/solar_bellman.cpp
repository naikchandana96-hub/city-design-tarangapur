#include <emscripten.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*
JSON FORMAT:
{
  "V": 5,
  "edges": [
    [0,1,6],
    [0,2,7],
    [1,3,5],
    [1,4,-4],
    [2,3,-3]
  ],
  "source": 0
}
*/

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_bellman(const char* jsonStr) {
    static string result;
    string s(jsonStr);

    int V = stoi(s.substr(s.find("V") + 3));
    int src = stoi(s.substr(s.find("source") + 9));

    vector<vector<int>> edges;
    int pos = s.find("edges");

    while (true) {
        int start = s.find("[", pos + 1);
        if (start == string::npos) break;
        int end = s.find("]", start);
        string row = s.substr(start + 1, end - start - 1);

        vector<int> e;
        stringstream ss(row);
        int x;
        while (ss >> x) {
            e.push_back(x);
            ss.ignore();
        }
        if (e.size() == 3) edges.push_back(e);
        pos = end;
    }

    vector<int> dist(V, 1e9);
    dist[src] = 0;

    for (int i = 1; i < V; i++)
        for (auto &e : edges)
            if (dist[e[0]] + e[2] < dist[e[1]])
                dist[e[1]] = dist[e[0]] + e[2];

    stringstream out;
    out << "Best Trading Prices:\n";
    for (int i = 0; i < V; i++)
        out << "Node " << i << " -> " << dist[i] << "\n";

    result = out.str();
    return result.c_str();
}

}
