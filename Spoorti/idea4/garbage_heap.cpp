#include <emscripten/emscripten.h>
#include <string>
#include <queue>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Waste {
    int amount;
    string zone;
};

struct Compare {
    bool operator()(Waste a, Waste b){
        return a.amount < b.amount;
    }
};

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_heap(const char* input) {
    static string output;
    output.clear();

    json j = json::parse(input);
    priority_queue<Waste, vector<Waste>, Compare> pq;

    for(auto &w : j["waste"]){
        pq.push({ w["amount"], w["zone"] });
    }

    while(!pq.empty()){
        Waste w = pq.top(); pq.pop();
        output += "Collecting " + w.zone +
                  " (Waste=" + to_string(w.amount) + ")\n";
    }

    return output.c_str();
}
}
