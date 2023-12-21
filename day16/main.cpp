#include <bits/stdc++.h>

using namespace std;

enum Dir { LEFT, UP, RIGHT, DOWN };

int dr[4] = {0,-1,0,1};
int dc[4] = {-1,0,1,0};

void dfs(vector<string>& grid, vector<vector<char>>& energized, int r, int c, char dir, bool first) {
    char m = (char)1 << dir;
    int rows = grid.size();
    int cols = grid[0].size();
    if (first);
    else if (energized[r][c] & m) return;
    else energized[r][c] |= m;
    r += dr[dir]; c += dc[dir];
    while (r >= 0 && c >= 0 && r < rows && c < cols && grid[r][c] == '.') {
        energized[r][c] |= m;
        r += dr[dir]; c += dc[dir];
    }
    if (r < 0 || c < 0 || r >= rows || c >= cols) return;
    char mirror = grid[r][c];

    // handle splits and no redir mirrors
    if (dir == LEFT || dir == RIGHT) {
        if (mirror == '-') {
            dfs(grid, energized, r, c, dir, false);
            return;
        } else if (mirror == '|') {
            dfs(grid, energized, r, c, UP, false);
            dfs(grid, energized, r, c, DOWN, false);
            return;
        }
    } else {
        if (mirror == '|') {
            dfs(grid, energized, r, c, dir, false);
            return;
        } else if (mirror == '-') {
            dfs(grid, energized, r, c, LEFT, false);
            dfs(grid, energized, r, c, RIGHT, false);
            return;
        }
    }
    dfs(grid, energized, r, c, mirror == '/' ? 3 - dir : (5 - dir) & 0b11, false);
}

int shoot(vector<string>& grid, int sr, int sc, Dir sdir) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<char>> energized(rows, vector<char>(cols, 0));
    dfs(grid, energized, sr - dr[sdir], sc - dc[sdir], sdir, true);
    int sum = 0;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            sum += (bool)energized[r][c];
    return sum;
}

void partA() {
    string line;
    vector<string> grid(1);
    while (getline(cin, grid.back()))
        grid.emplace_back();
    grid.pop_back();
    cout << shoot(grid, 0, 0, RIGHT) << endl;
}

void partB() {
    string line;
    vector<string> grid(1);
    while (getline(cin, grid.back()))
        grid.emplace_back();
    grid.pop_back();
    int rows = grid.size();
    int cols = grid[0].size();
    int maxEnergized = 0;
    for (int r = 0; r < rows; ++r)
        maxEnergized = max(maxEnergized, max(shoot(grid, r, 0, RIGHT), shoot(grid, r, cols-1, LEFT)));
    for (int c = 0; c < cols; ++c)
        maxEnergized = max(maxEnergized, max(shoot(grid, 0, c, DOWN), shoot(grid, rows-1, c, UP)));
    cout << maxEnergized << endl;
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
    cout << chrono::duration_cast<chrono::microseconds>(end - start).count() << "ms" << endl;
}