#include <emscripten/emscripten.h>
#include <string>
#include <queue>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Trip {
    int waitTime;
    string routeName;
};

struct CompareTrips {
    bool operator()(Trip a, Trip b) {
        return a.waitTime > b.waitTime; // min-heap
    }
};

priority_queue<Trip, vector<Trip>, CompareTrips> tripSchedule;

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_heap(const char* input) {
    static string output;
    output.clear();

    json j = json::parse(input);
    auto trips = j["trips"];

    while(!tripSchedule.empty()) tripSchedule.pop();

    for(auto &t : trips){
        tripSchedule.push({t["waitTime"], t["routeName"]});
    }

    output += "Scheduled Trips by Wait Time:\n";
    while(!tripSchedule.empty()){
        Trip t = tripSchedule.top(); tripSchedule.pop();
        output += t.routeName + " | Wait Time: " + to_string(t.waitTime) + " minutes\n";
    }

    return output.c_str();
}
}
