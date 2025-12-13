#include <emscripten.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/*
JSON FORMAT:
{
  "nodes": 6,
  "adj": [
    [1,2],
    [0,3],
    [0,4],
    [1,5],
    [2],
    [3]
  ]
}
*/

void dfsUtil(int u, vector<vector<int>>& adj, vector<bool>& vis, stringstream& out) {
    vis[u] = true;
    out << "Energy Node: " << u << "\n";
    for (int v : adj[u]) {
        if (!vis[v]) dfsUtil(v, adj, vis, out);
    }
}

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_dfs(const char* jsonStr) {
    static string result;
    string s(jsonStr);

    int n = stoi(s.substr(s.find("nodes") + 7));
    vector<vector<int>> adj(n);

    int pos = s.find("adj");
    pos = s.find("[", pos);

    for (int i = 0; i < n; i++) {
        pos = s.find("[", pos + 1);
        int end = s.find("]", pos);
        string row = s.substr(pos + 1, end - pos - 1);

        stringstream ss(row);
        int x;
        while (ss >> x) {
            adj[i].push_back(x);
            ss.ignore();
        }
        pos = end;
    }

    vector<bool> vis(n, false);
    stringstream out;
    out << "DFS Energy Flow:\n";

    for (int i = 0; i < n; i++)
        if (!vis[i]) dfsUtil(i, adj, vis, out);

    result = out.str();
    return result.c_str();
}

}
