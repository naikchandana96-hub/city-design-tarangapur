#include <emscripten/emscripten.h>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<int> segTree;
vector<int> arr;

void build(int idx, int l, int r) {
    if (l == r) {
        segTree[idx] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(idx*2, l, mid);
    build(idx*2+1, mid+1, r);
    segTree[idx] = min(segTree[idx*2], segTree[idx*2+1]);
}

int query(int idx, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) return 1e9;
    if (ql <= l && r <= qr) return segTree[idx];
    int mid = (l + r) / 2;
    return min(
        query(idx*2, l, mid, ql, qr),
        query(idx*2+1, mid+1, r, ql, qr)
    );
}

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_segment_tree(const char* jsonInput) {
    arr.clear();

    string s(jsonInput);
    int num = 0;
    bool reading = false;

    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
            reading = true;
        } else if (reading) {
            arr.push_back(num);
            num = 0;
            reading = false;
        }
    }
    if (reading) arr.push_back(num);

    int n = arr.size();
    segTree.assign(4*n, 0);
    build(1, 0, n-1);

    int result = query(1, 0, n-1, 1, 4);

    static string output;
    output = "Minimum moisture between index 1 and 4 = " + to_string(result);
    return output.c_str();
}
}
