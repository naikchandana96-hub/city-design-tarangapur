#include <emscripten/emscripten.h>
#include <string>
#include <queue>
#include <vector>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

extern "C" {

EMSCRIPTEN_KEEPALIVE
const char* run_bfs(const char* input) {
    static string output;
    output.clear();

    json j = json::parse(input);
    vector<vector<int>> grid = j["grid"];

    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    queue<pair<int,int>> q;

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(grid[i][j] == 1 && !visited[i][j]){
                q.push({i,j});
                visited[i][j] = true;

                while(!q.empty()){
                    auto [x,y] = q.front(); q.pop();
                    output += "Debris at (" + to_string(x) + "," + to_string(y) + ")\n";

                    for(int k=0;k<4;k++){
                        int nx = x + dx[k];
                        int ny = y + dy[k];
                        if(nx>=0 && ny>=0 && nx<rows && ny<cols &&
                           grid[nx][ny]==1 && !visited[nx][ny]){
                            visited[nx][ny] = true;
                            q.push({nx,ny});
                        }
                    }
                }
            }
        }
    }
    return output.c_str();
}
}
