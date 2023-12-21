#include <bits/stdc++.h>

using namespace std;

int calcA(vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<long long> reps(max(rows, cols), 0);

    auto findMirror = [&](int len) {
        for (int i = 0; i < len-1; ++i) {
            bool valid = true;
            int cap = min(len-i-1, i+1);
            for (int j = 0; valid && j < cap; ++j)
                valid = reps[i-j] == reps[i+j+1];
            if (valid) return i+1;
        }
        return -1;
    };

    // find row mirror
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c)
            reps[r] = (reps[r] << 1) | (grid[r][c] == '#');
    }
    int mirror;
    if ((mirror = findMirror(rows)) != -1) return mirror * 100;

    // find col mirror
    memset(&reps[0], 0, rows * sizeof(long long));
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c)
            reps[c] = (reps[c] << 1) | (grid[r][c] == '#');
    }
    if ((mirror = findMirror(cols)) != -1) return mirror;
    return 0;
}

int calcB(vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<long long> reps(max(rows, cols), 0);

    auto findMirror = [&](int len) {
        for (int i = 0; i < len-1; ++i) {
            char edits = 0;
            int cap = min(len-i-1, i+1);
            for (int j = 0; edits <= 1 && j < cap; ++j) {
                long long x = reps[i-j] ^ reps[i+j+1];
                if (x) ++edits += (x ^ (x & (-x))) != 0;
            }
            if (edits == 1) return i+1;
        }
        return -1;
    };

    // find row mirror
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c)
            reps[r] = (reps[r] << 1) | (grid[r][c] == '#');
    }
    int mirror;
    if ((mirror = findMirror(rows)) != -1) return mirror * 100;

    // find col mirror
    memset(&reps[0], 0, rows * sizeof(long long));
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c)
            reps[c] = (reps[c] << 1) | (grid[r][c] == '#');
    }
    if ((mirror = findMirror(cols)) != -1) return mirror;
    return 0;
}

void solve(bool part) {
    vector<string> grid(1);
    int sum = 0;
    while (getline(cin, grid.back())) {
        if (grid.back().empty()) {
            grid.pop_back();
            sum += part ? calcB(grid) : calcA(grid);
            grid.clear();
        }
        grid.emplace_back();
    }
    grid.pop_back();
    sum += part ? calcB(grid) : calcA(grid);
    cout << sum << endl;
}

void partA() {
    solve(false);
}

void partB() {
    solve(true);
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