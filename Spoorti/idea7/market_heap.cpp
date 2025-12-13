#include <emscripten/emscripten.h>
#include <queue>
#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Crop {
    int demand;
    string name;
};

struct Compare {
    bool operator()(Crop a, Crop b) {
        return a.demand < b.demand; // max-heap
    }
};

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_heap(const char* input){
    static string output;
    output.clear();

    json j = json::parse(input);
    auto crops_json = j["crops"];

    priority_queue<Crop, vector<Crop>, Compare> pq;
    for(auto& c : crops_json){
        pq.push({c["demand"], c["name"]});
    }

    while(!pq.empty()){
        Crop c = pq.top(); pq.pop();
        output += "High-Demand Crop: " + c.name + " | Demand Score: " + to_string(c.demand) + "\n";
    }

    return output.c_str();
}
}
