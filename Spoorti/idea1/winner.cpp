#include <string>
#include <emscripten.h>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_winner(const char* jsonStr) {
    static string result;
    result.clear();

    json data = json::parse(jsonStr);

    int maxBid = 0;
    string buyer;

    for (auto &b : data["bids"]) {
        if (b["amount"] > maxBid) {
            maxBid = b["amount"];
            buyer = b["buyer"];
        }
    }

    result = "🏆 WINNER 🏆\nBuyer: " + buyer +
             "\nWinning Bid: Rs." + to_string(maxBid);

    return result.c_str();
}

}
