#include <string>
#include <sstream>
#include <emscripten.h>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_avl(const char* jsonStr) {
    static string result;
    result.clear();

    json data = json::parse(jsonStr);

    for (auto &f : data["fish_listings"]) {
        result += f["name"].get<string>();
        result += " - Rs.";
        result += to_string((int)f["price"]);
        result += "\n";
    }

    return result.c_str();
}

}
