#include <bits/stdc++.h>

using namespace std;

void tiltUp(vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<int> nextEmpty(cols, -1);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '#') {
                nextEmpty[c] = r;
                continue;
            }
            if (grid[r][c] != 'O') continue;
            while (grid[++nextEmpty[c]][c] == '#');
            swap(grid[r][c], grid[nextEmpty[c]][c]);
        }
    }
}

void tiltDown(vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<int> nextEmpty(cols, rows);
    for (int r = rows-1; r >= 0; --r) {
        for (int c = cols-1; c >= 0; --c) {
            if (grid[r][c] == '#') {
                nextEmpty[c] = r;
                continue;
            }
            if (grid[r][c] != 'O') continue;
            while (grid[--nextEmpty[c]][c] == '#');
            swap(grid[r][c], grid[nextEmpty[c]][c]);
        }
    }
}

void tiltLeft(vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<int> nextEmpty(rows, -1);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '#') {
                nextEmpty[r] = c;
                continue;
            }
            if (grid[r][c] != 'O') continue;
            while (grid[r][++nextEmpty[r]] == '#');
            swap(grid[r][c], grid[r][nextEmpty[r]]);
        }
    }
}

void tiltRight(vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<int> nextEmpty(rows, cols);
    for (int r = rows-1; r >= 0; --r) {
        for (int c = cols-1; c >= 0; --c) {
            if (grid[r][c] == '#') {
                nextEmpty[r] = c;
                continue;
            }
            if (grid[r][c] != 'O') continue;
            while (grid[r][--nextEmpty[r]] == '#');
            swap(grid[r][c], grid[r][nextEmpty[r]]);
        }
    }
}

int calcLoad(vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int load = 0;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (grid[r][c] == 'O') load += rows - r;
    return load;
}

vector<int> calcState(vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<int> state;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (grid[r][c] == 'O') state.emplace_back((r << 16) | c);
    return state;
}

vector<string> readInput() {
    vector<string> grid(1);
    while (getline(cin, grid.back()))
        grid.emplace_back();
    grid.pop_back();
    return grid;
}

void partA() {
    vector<string> grid = readInput();
    tiltUp(grid);
    cout << calcLoad(grid) << endl;
}

void partB() {
    vector<string> grid = readInput();
    map<vector<int>,int> visited;
    int remaining = 1000000000;
    while (remaining--) {
        tiltUp(grid);
        tiltLeft(grid);
        tiltDown(grid);
        tiltRight(grid);
        vector<int> state = calcState(grid);
        auto it = visited.find(state);
        if (it == visited.end()) {
            visited[state] = remaining;
        } else {
            int cycle = remaining - it->second;
            remaining %= cycle;
        }
    }
    cout << calcLoad(grid) << endl;
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