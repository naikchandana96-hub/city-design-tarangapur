#include <emscripten.h>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Edge {
    int u, v, w;
};

vector<int> parent;

int findSet(int v) {
    if (v == parent[v]) return v;
    return parent[v] = findSet(parent[v]);
}

void unionSet(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) parent[b] = a;
}

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_kruskal(const char* jsonStr) {
    static string result;
    stringstream ss;

    json j = json::parse(jsonStr);
    int n = j["nodes"];
    vector<Edge> edges;

    for (auto& e : j["edges"]) {
        edges.push_back({e["u"], e["v"], e["w"]});
    }

    parent.resize(n);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b) { return a.w < b.w; });

    ss << "Eco-Friendly Minimum Spanning Tree:\n";

    for (auto& e : edges) {
        if (findSet(e.u) != findSet(e.v)) {
            ss << e.u << " -- " << e.v
               << " (cost " << e.w << ")\n";
            unionSet(e.u, e.v);
        }
    }

    result = ss.str();
    return result.c_str();
}

}
