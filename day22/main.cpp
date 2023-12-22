#include <bits/stdc++.h>

using namespace std;

struct Brick {
    int bounds[3][2] = {{0,0},{0,0},{0,0}};
};

tuple<vector<Brick>, vector<unordered_set<int>>, vector<unordered_set<int>>, vector<unordered_set<int>>> construct() {
    string line;
    vector<Brick> bricks;
    while (getline(cin, line)) {
        line.push_back(',');
        int i;
        int j = 0;
        bricks.emplace_back();
        auto& brick = bricks.back().bounds;
        for (i = 0; line[i] != '~'; ++i) {
            if (line[i] == ',') {
                ++j;
                continue;
            }
            brick[j][0] = brick[j][0] * 10 + (line[i] - '0');
        }
        j = 0;
        for (++i; i < line.size(); ++i) {
            if (line[i] == ',') {
                ++j;
                continue;
            }
            brick[j][1] = brick[j][1] * 10 + (line[i] - '0');
        }
    }

    sort(bricks.begin(), bricks.end(), [](Brick& a, Brick& b) {
        return a.bounds[2][0] < b.bounds[2][0];
    });
    vector<unordered_set<int>> sittingOn(bricks.size());
    vector<unordered_set<int>> holdingUp(bricks.size());
    vector<unordered_set<int>> soleSupporter(bricks.size());
    for (int i = 0; i < bricks.size(); ++i) {
        int floor = 0;
        Brick& above = bricks[i];

        // detect collision
        for (int j = 0; j < i; ++j) {
            Brick& below = bricks[j];
            if (below.bounds[2][1] < floor
                || above.bounds[0][0] > below.bounds[0][1]
                || below.bounds[0][0] > above.bounds[0][1]
                || above.bounds[1][0] > below.bounds[1][1]
                || below.bounds[1][0] > above.bounds[1][1]
            ) continue;
            if (floor < below.bounds[2][1])
                sittingOn[i].clear();
            floor = below.bounds[2][1];
            sittingOn[i].insert(j);
        }
        if (sittingOn[i].size() == 1)
            soleSupporter[*sittingOn[i].begin()].insert(i);
        for (int j : sittingOn[i])
            holdingUp[j].insert(i);

        // drop brick
        int dz = above.bounds[2][0] - floor - 1;
        above.bounds[2][0] -= dz;
        above.bounds[2][1] -= dz;
    }
    return {bricks, sittingOn, holdingUp, soleSupporter};
}

void partA() {
    auto&& [bricks, sittingOn, holdingUp, soleSupporter] = construct();
    int res = 0;
    for (auto& x : soleSupporter)
        res += x.empty();
    cout << res << endl;
}

int removeBrick(vector<Brick>& bricks, vector<unordered_set<int>>& sittingOn, vector<unordered_set<int>>& holdingUp, vector<unordered_set<int>>& soleSupporter, int target) {
    int ret = 1;
    for (int above : holdingUp[target]) {
        sittingOn[above].erase(target);
        if (sittingOn[above].size() == 1)
            soleSupporter[*sittingOn[above].begin()].insert(above);
    }
    for (int next : soleSupporter[target])
        ret += removeBrick(bricks, sittingOn, holdingUp, soleSupporter, next);
    return ret;
}

void partB() {
    auto&& [bricks, sittingOn, holdingUp, soleSupporter] = construct();
    int res = 0;
    for (int i = 0; i < bricks.size(); ++i) {
        if (soleSupporter[i].empty()) continue;
        auto soCopy = sittingOn;
        auto ssCopy = soleSupporter;
        res += removeBrick(bricks, soCopy, holdingUp, ssCopy, i) - 1;
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