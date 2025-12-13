#include <emscripten.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_bfs(const char* jsonStr) {
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

    vector<vector<int>> adj(n);

    // Parse adjacency list safely
    int pos = s.find("adj");
    pos = s.find("[", pos);
    for (int i = 0; i < n; i++) {
        pos = s.find("[", pos + 1);
        int end_row = s.find("]", pos);
        string row = s.substr(pos + 1, end_row - pos - 1);

        stringstream ss(row);
        string token;
        while (getline(ss, token, ',')) {
            stringstream ts(token);
            int num;
            if (ts >> num) adj[i].push_back(num);
        }

        pos = end_row;
    }

    vector<bool> vis(n, false);
    stringstream out;
    out << "BFS Fuel Zones:\n";

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            queue<int> q;
            q.push(i);
            vis[i] = true;

            while (!q.empty()) {
                int u = q.front(); q.pop();
                out << "Monitoring Fuel Zone: " << u << "\n";
                for (int v : adj[u]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }

    result = out.str();
    return result.c_str();
}

}
