#include <emscripten/emscripten.h>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Field {
    int moisture;
    string name;
};

struct Compare {
    bool operator()(Field a, Field b) {
        return a.moisture > b.moisture;
    }
};

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_min_heap(const char* jsonInput) {
    priority_queue<Field, vector<Field>, Compare> pq;

    string s(jsonInput);
    string name = "";
    int moisture = 0;
    bool readingName = false;

    for (char c : s) {
        if (c == '"') {
            readingName = !readingName;
            if (!readingName && !name.empty() && moisture > 0) {
                pq.push({moisture, name});
                name = "";
                moisture = 0;
            }
        } else if (readingName && isalpha(c)) {
            name += c;
        } else if (isdigit(c)) {
            moisture = moisture * 10 + (c - '0');
        }
    }

    Field driest = pq.top();

    static string output;
    output = "Highest priority field: " + driest.name +
             " (Moisture = " + to_string(driest.moisture) + ")";
    return output.c_str();
}
}
