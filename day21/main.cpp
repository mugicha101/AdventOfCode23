#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void partA() {
    vector<string> grid(1);
    while (getline(cin, grid.back()))
        grid.emplace_back();
    grid.pop_back();
    int rows = grid.size(), cols = grid[0].size();
    int sr, sc;
    for (sr = 0; sr < rows; ++sr) {
        for (sc = 0; sc < cols; ++sc) {
            if (grid[sr][sc] == 'S') goto J;
        }
    }
    J:;

    // chess parity of tile must match parity of number of moves
    // if shortest path less than steps, can go back and forth until at steps (assuming parity matches)
    // can just check if parity matches and reachible in given steps
    const int STEPS = 64;
    queue<pair<int,int>> q;
    grid[sr][sc] = 'X';
    q.emplace(sr, sc);
    for (int s = 0; s < STEPS; ++s) {
        for (int qi = q.size(); qi > 0; --qi) {
            auto [r, c] = q.front();
            q.pop();
            auto check = [&](int r, int c) {
                if (grid[r][c] != '.') return;
                grid[r][c] = 'X';
                q.emplace(r, c);
            };
            if (r) check(r-1, c);
            if (c) check(r, c-1);
            if (r+1 < rows) check(r+1, c);
            if (c+1 < cols) check(r, c+1);
        }
    }
    int count = 0;
    int p = (sr + sc + STEPS) & 1;
    for (int r = 0; r < rows; ++r)
        for (int c = (p + r) & 1; c < cols; c += 2)
            count += grid[r][c] == 'X';
    cout << count << endl;
}

void partB() {
    vector<string> grid(1);
    while (getline(cin, grid.back()))
        grid.emplace_back();
    grid.pop_back();

    // assume cardinal directions are clear from start and that each tile can be reached in its shortest distance (valid under the input)
    // calculate the number of instances each matching parity walkable tile appears within the steps diamond
    // even better, the diamond aligns perfectly with the grid
    // sectors:
    /*
      1 1 0 1 1
      1 0 0 0 1
      0 0 0 0 0
      1 0 0 0 1
      1 1 0 1 1
    */

    ll sectors[2][2] = {{0,0},{0,0}};
    const int steps = 26501365;
    const int o = 65;
    const int dim = 131;
    const int p = steps & 1;
    grid[o][o] = '.';

    // figure out which tiles are reachible first
    queue<pair<int,int>> q;
    q.emplace(o, o);
    grid[o][o] = 'X';
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        auto check = [&](int r, int c) {
            if (grid[r][c] != '.') return;
            grid[r][c] = 'X';
            q.emplace(r, c);
        };
        if (r) check(r-1, c);
        if (c) check(r, c-1);
        if (r+1 < dim) check(r+1, c);
        if (c+1 < dim) check(r, c+1);
    }
    for (int r = 0; r < dim; ++r) {
        for (int c = 0; c < dim; ++c) {
            if (grid[r][c] == 'X') grid[r][c] = '.';
            else if (grid[r][c] == '.') grid[r][c] = '#';
        }
    }

    // calc sectors
    auto handle = [&](int r, int c, int s) {
        sectors[s][(r + c + p) & 1] += grid[r][c] == '.';
    };
    for (int r = 0; r < o; ++r) {
        for (int c = 0; c < o-r; ++c) handle(r, c, 1);
        for (int c = o-r; c <= o+r; ++c) handle(r, c, 0);
        for (int c = o+r+1; c < dim; ++c) handle(r, c, 1);
    }
    for (int r = o; r < dim; ++r) {
        for (int c = 0; c < r-o; ++c) handle(r, c, 1);
        for (int c = r-o; c < dim-(r-o); ++c) handle(r, c, 0);
        for (int c = dim-(r-o); c < dim; ++c) handle(r, c, 1);
    }
    ll totals[2] = { sectors[0][0] + sectors[1][0], sectors[0][1] + sectors[1][1] };
    ll chunkRadius = (steps - o) / dim;
    int pEdge = chunkRadius & 1;
    ll area = totals[0];
    for (int r = 1; r <= chunkRadius; ++r)
        area += totals[r & 1] * r * 4;
    area -= sectors[1][pEdge] * (chunkRadius + 1);
    area += sectors[1][1-pEdge] * chunkRadius;
    cout << area << endl;
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