#include <bits/stdc++.h>

using namespace std;

void partA() {
    vector<string> grid(1);
    while (getline(cin, grid.back()))
        grid.emplace_back();
    grid.pop_back();
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<int>> maxDist(rows, vector<int>(cols, 0));
    vector<tuple<int,int,int,char>> heap;
    heap.emplace_back(0, 1, 0, 4);
    maxDist[0][1] = 0;
    auto cmp = [](tuple<int,int,int,char>& a, tuple<int,int,int,char>& b) {
        return get<2>(a) < get<2>(b);
    };
    while (!heap.empty()) {
        auto [r, c, d, s] = heap.front();
        char tile = grid[r][c];
        pop_heap(heap.begin(), heap.end(), cmp);
        heap.pop_back();
        if (d < maxDist[r][c]) continue;
        ++d;
        auto check = [&](int nr, int nc, char ns) {
            if (grid[nr][nc] == '#' || maxDist[nr][nc] >= d) return;
            maxDist[nr][nc] = d;
            heap.emplace_back(nr, nc, d, ns);
            push_heap(heap.begin(), heap.end(), cmp);
        };
        if (s != 2 && r && (tile == '.' || tile == '^')) check(r-1, c, 0);
        if (s != 3 && c && (tile == '.' || tile == '<')) check(r, c-1, 1);
        if (s != 0 && r+1 < rows && (tile == '.' || tile == 'v')) check(r+1, c, 2);
        if (s != 1 && c+1 < cols && (tile == '.' || tile == '>')) check(r, c+1, 3);
    }
    cout << maxDist[rows-1][cols-2] << endl;
}

void nextXing(vector<string>& grid, vector<pair<int,int>>& reachedXings, int r, int c, int d, int s) {
    if (grid[r][c] == 'X') {
        reachedXings.emplace_back((r << 16) | c, d);
        return;
    }
    auto check = [&](int r, int c, int s) {
        if (grid[r][c] == '#') return;
        nextXing(grid, reachedXings, r, c, d+1, s);
    };
    int rows = grid.size();
    int cols = grid[0].size();
    if (r && s != 2) check(r-1, c, 0);
    if (c && s != 3) check(r, c-1, 1);
    if (r+1 < rows && s != 0) check(r+1, c, 2);
    if (c+1 < cols && s != 1) check(r, c+1, 3);
}

int dfs(vector<vector<pair<int,int>>>& adj, vector<bool>& visited, int curr, int dist) {
    if (curr == adj.size()-1) return dist;
    int ret = 0;
    visited[curr] = true;
    for (auto& [next, nextDist] : adj[curr]) {
        if (visited[next]) continue;
        ret = max(ret, dfs(adj, visited, next, dist + nextDist));
    }
    visited[curr] = false;
    return ret;
}

void partB() {
    vector<string> grid(1);
    while (getline(cin, grid.back()))
        grid.emplace_back();
    grid.pop_back();
    int rows = grid.size();
    int cols = grid[0].size();
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '#' || grid[r][c] == '.') continue;
            grid[r][c] = '.';
        }
    }
    vector<pair<int,int>> xings;
    grid[0][1] = 'X';
    grid[rows-1][cols-2] = 'X';
    map<int,int> xingMap;
    for (int r = 1; r < rows-1; ++r) {
        for (int c = 1; c < cols-1; ++c) {
            if (grid[r][c] == '#') continue;
            int dirs = (int)(grid[r-1][c] == '.') + (int)(grid[r+1][c] == '.') + (int)(grid[r][c-1] == '.') + (int)(grid[r][c+1] == '.');
            if (dirs < 3) continue;
            grid[r][c] = 'X'; 
        }
    }
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] != 'X') continue;
            xingMap[(r << 16) | c] = xings.size();
            xings.emplace_back(r, c);
        }
    }

    // form undirected graph of xings
    vector<vector<pair<int,int>>> xingAdj(xings.size());
    for (int i = 0; i < xings.size(); ++i) {
        auto [xr, xc] = xings[i];
        grid[xr][xc] = '.';
        vector<pair<int,int>> reachedXings;
        nextXing(grid, reachedXings, xr, xc, 0, 4);
        for (auto& [x, d] : reachedXings)
            xingAdj[i].emplace_back(xingMap[x], d);
        grid[xr][xc] = 'X';
    }

    // dfs
    vector<bool> visited(xings.size(), false);
    int steps = dfs(xingAdj, visited, 0, 0);
    cout << steps << endl;
}


int main(int argc, char **argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);
    cout << setprecision(12);
    freopen("./input.txt","r",stdin);
    auto start = chrono::high_resolution_clock::now();
    argv[1][0] == 'A' ? partA() : partB();
    auto end = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>(end - start).count() << "microseconds" << endl;
}