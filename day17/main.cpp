#include <bits/stdc++.h>

using namespace std;

enum Dir { LEFT, UP, RIGHT, DOWN };
int dr[] = {0,-1,0,1};
int dc[] = {-1,0,1,0};

struct State {
    Dir dir;
    int s, r, c, dist;
    State() {}
    State(Dir dir, int s, int r, int c, int dist) : dir(dir), s(s), r(r), c(c), dist(dist) {}
};

void partA() {
    string line;
    vector<string> grid(1);
    while (getline(cin, grid.back()))
        grid.emplace_back();
    grid.pop_back();
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<vector<int>>> dist(12, vector<vector<int>>(rows, vector<int>(cols, INT_MAX)));
    auto getDist = [&](State& state) {
        return &dist[(state.s << 2) | state.dir][state.r][state.c];
    };
    vector<State> heap;
    auto cmp = [](State& a, State& b) {
        return a.dist > b.dist;
    };
    heap.emplace_back(RIGHT, 2, 0, 1, 0);
    *getDist(heap.back()) = 0;
    heap.emplace_back(DOWN, 2, 1, 0, 0);
    *getDist(heap.back()) = 0;
    make_heap(heap.begin(), heap.end(), cmp);
    int res = -1;
    while (true) {
        pop_heap(heap.begin(), heap.end(), cmp);
        State state = heap.back();
        heap.pop_back();
        state.dist += grid[state.r][state.c] - '0';
        if (state.r == rows - 1 && state.c == cols - 1) {
            res = state.dist;
            break;
        }
        auto check = [&](State state) {
            if (state.r < 0 || state.c < 0 || state.r >= rows || state.c >= cols)
                return;
            int* d = getDist(state);
            if (*d <= state.dist) return;
            heap.push_back(state);
            push_heap(heap.begin(), heap.end(), cmp);
        };
        if (state.s) check(State(state.dir, state.s - 1, state.r + dr[state.dir], state.c + dc[state.dir], state.dist));
        Dir left = (Dir)(((int)state.dir + 3) & 0b11);
        Dir right = (Dir)(((int)state.dir + 1) & 0b11);
        check(State(left, 2, state.r + dr[left], state.c + dc[left], state.dist));
        check(State(right, 2, state.r + dr[right], state.c + dc[right], state.dist));
    }
    cout << res << endl;
}

void partB() {
    string line;
    vector<string> grid(1);
    while (getline(cin, grid.back()))
        grid.emplace_back();
    grid.pop_back();
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<vector<int>>> dist(4 * 10, vector<vector<int>>(rows, vector<int>(cols, INT_MAX)));
    auto getDist = [&](State& state) {
        return &dist[(state.s << 2) | (int)state.dir][state.r][state.c];
    };
    vector<State> heap;
    auto cmp = [](State& a, State& b) {
        return a.dist > b.dist;
    };
    heap.emplace_back(RIGHT, 9, 0, 1, 0);
    *getDist(heap.back()) = 0;
    heap.emplace_back(DOWN, 9, 1, 0, 0);
    *getDist(heap.back()) = 0;
    make_heap(heap.begin(), heap.end(), cmp);
    int res = -1;
    while (true) {
        pop_heap(heap.begin(), heap.end(), cmp);
        State state = heap.back();
        heap.pop_back();
        state.dist += grid[state.r][state.c] - '0';
        if (state.s <= 6 && state.r == rows - 1 && state.c == cols - 1) {
            res = state.dist;
            break;
        }
        auto check = [&](State state) {
            if (state.r < 0 || state.c < 0 || state.r >= rows || state.c >= cols)
                return;
            int* d = getDist(state);
            if (*d <= state.dist) return;
            *d = state.dist;
            heap.push_back(state);
            push_heap(heap.begin(), heap.end(), cmp);
        };
        if (state.s) check(State(state.dir, state.s - 1, state.r + dr[state.dir], state.c + dc[state.dir], state.dist));
        if (state.s <= 6) {
            Dir left = (Dir)(((int)state.dir + 3) & 0b11);
            Dir right = (Dir)(((int)state.dir + 1) & 0b11);
            check(State(left, 9, state.r + dr[left], state.c + dc[left], state.dist));
            check(State(right, 9, state.r + dr[right], state.c + dc[right], state.dist));
        }
    }
    cout << res << endl;
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