#include <bits/stdc++.h>

using namespace std;

enum Dir { LEFT, RIGHT, UP, DOWN };

struct Pipe {
    char v;
    bool inline left() const { return (v >> 3) & 1; }
    bool inline right() const { return (v >> 2) & 1; }
    bool inline up() const { return (v >> 1) & 1; }
    bool inline down() const { return v & 1; }
};

Pipe pipe[256];
void initPipe() {
    pipe['|'].v = 0b0011;
    pipe['-'].v = 0b1100;
    pipe['L'].v = 0b0110;
    pipe['J'].v = 0b1010;
    pipe['7'].v = 0b1001;
    pipe['F'].v = 0b0101;
    pipe['.'].v = 0b0000;
    pipe['S'].v = 0b1111;
}

int dfsA(vector<string>& grid, Dir dir, int r, int c) {
    char curr = grid[r][c];
    if (curr == 'S') return 1;
    int ret = INT_MIN;
    if (pipe[curr].left() && dir != RIGHT && c && pipe[grid[r][c-1]].right()) {
        ret = max(ret, 1 + dfsA(grid, LEFT, r, c-1));
    }
    if (pipe[curr].right() && dir != LEFT && c+1 < grid[0].size() && pipe[grid[r][c+1]].left()) {
        ret = max(ret, 1 + dfsA(grid, RIGHT, r, c+1));
    }
    if (pipe[curr].up() && dir != DOWN && r && pipe[grid[r-1][c]].down()) {
        ret = max(ret, 1 + dfsA(grid, UP, r-1, c));
    }
    if (pipe[curr].down() && dir != UP && r+1 < grid.size() && pipe[grid[r+1][c]].up()) {
        ret = max(ret, 1 + dfsA(grid, DOWN, r+1, c));
    }
    return ret;
}

void partA() {
    initPipe();
    string line;
    vector<string> grid(1);
    while (getline(cin, grid.back()))
        grid.emplace_back();
    grid.pop_back();
    int rows = grid.size();
    int cols = grid[0].size();
    int sr, sc;
    bool startFound = false;
    for (sr = 0; !startFound && sr < rows; ++sr)
        for (sc = 0; !startFound && sc < cols; ++sc)
            startFound = grid[sr][sc] == 'S';
    --sr; --sc;

    int dist = 0;
    if (sr && pipe[grid[sr-1][sc]].down()) {
        dist = dfsA(grid, UP, sr-1, sc);
    } else if (sr < rows-1 && pipe[grid[sr+1][sc]].up()) {
        dist = dfsA(grid, DOWN, sr+1, sc);
    } else if (sc && pipe[grid[sr][sc-1]].right()) {
        dist = dfsA(grid, LEFT, sr, sc-1);
    } else if (sc < cols-1 && pipe[grid[sr][sc+1]].left()) {
        dist = dfsA(grid, RIGHT, sr, sc+1);
    }
    cout << (dist >> 1) << endl;
}

void dfsB(vector<string>& grid, vector<tuple<int,int,char>>& path, Dir dir, int r, int c) {
    char curr = grid[r][c];
    path.emplace_back(r, c, curr);
    if (curr == 'S') {
        return;
    }
    if (pipe[curr].left() && dir != RIGHT && c && pipe[grid[r][c-1]].right()) {
        dfsB(grid, path, LEFT, r, c-1);
    }
    if (pipe[curr].right() && dir != LEFT && c+1 < grid[0].size() && pipe[grid[r][c+1]].left()) {
        dfsB(grid, path, RIGHT, r, c+1);
    }
    if (pipe[curr].up() && dir != DOWN && r && pipe[grid[r-1][c]].down()) {
        dfsB(grid, path, UP, r-1, c);
    }
    if (pipe[curr].down() && dir != UP && r+1 < grid.size() && pipe[grid[r+1][c]].up()) {
        dfsB(grid, path, DOWN, r+1, c);
    }
}

void partB() {
    initPipe();
    string line;
    vector<string> grid(1);
    while (getline(cin, grid.back()))
        grid.emplace_back();
    grid.pop_back();
    int rows = grid.size();
    int cols = grid[0].size();
    int sr, sc;
    bool startFound = false;
    for (sr = 0; !startFound && sr < rows; ++sr)
        for (sc = 0; !startFound && sc < cols; ++sc)
            startFound = grid[sr][sc] == 'S';
    --sr; --sc;

    bool up = sr && pipe[grid[sr-1][sc]].down();
    bool down = sr < rows-1 && pipe[grid[sr+1][sc]].up();
    bool left = sc && pipe[grid[sr][sc-1]].right();
    bool right = sc < cols-1 && pipe[grid[sr][sc+1]].left();

    // find path
    vector<tuple<int,int,char>> path;
    if (up) {
        dfsB(grid, path, UP, sr-1, sc);
    } else if (down) {
        dfsB(grid, path, DOWN, sr+1, sc);
    } else if (left) {
        dfsB(grid, path, LEFT, sr, sc-1);
    } else if (right) {
        dfsB(grid, path, RIGHT, sr, sc+1);
    }

    // clear rest of grid
    for (int r = 0; r < rows; ++r)
        grid[r] = string(cols, '.');
    for (auto& tile : path) {
        auto& [r, c, s] = tile;
        grid[r][c] = s;
    }
    char startState = ((char)left << 3) | ((char)right << 2) | ((char)up << 1) | (char)down;
    char syms[] = {'-', '|', 'L', 'J', 'F', '7'};
    for (char p : syms) {
        if (pipe[p].v == startState) {
            grid[sr][sc] = p;
            break;
        }
    }

    // check if each island is in loop
    int sum = 0;
    for (int tr = 0; tr < rows; ++tr) {
        for (int tc = 0; tc < cols; ++tc) {
            if (grid[tr][tc] != '.') continue;
            queue<pair<int,int>> q;
            q.emplace(tr, tc);
            grid[tr][tc] = 'X';

            // get island
            int count = 0;
            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                ++count;
                auto check = [&](int r, int c) {
                    if (grid[r][c] != '.') return;
                    q.emplace(r, c);
                    grid[r][c] = 'X';
                };
                if (r) check(r-1, c);
                if (c) check(r, c-1);
                if (r+1 < rows) check(r+1, c);
                if (c+1 < cols) check(r, c+1);
            }
            
            // count parity
            bool inLoop = false;
            int t = tr;
            while (--t >= 0) {
                switch (grid[t][tc]) {
                    case '-': case 'F': case 'L': inLoop = !inLoop;
                }
            }
            if (inLoop) sum += count;
        }
    }
    cout << sum << endl;
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