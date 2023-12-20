#include <bits/stdc++.h>

using namespace std;

void solve(int expansion) {
    string line;
    vector<pair<int,int>> points;
    vector<int> colData;
    int r = 0;
    while (getline(cin, line)) {
        bool empty = true;
        colData.resize(line.size(), expansion);
        for (int c = 0; c < line.size(); ++c) {
            if (line[c] != '#') continue;
            colData[c] = 1;
            empty = false;
            points.emplace_back(r, c);
        }
        r += empty ? expansion : 1;
    }
    for (int i = 1; i < colData.size(); ++i)
        colData[i] += colData[i-1];
    for (auto& p : points) p.second = colData[p.second];
    long long sum = 0;
    for (int i = 1; i < points.size(); ++i)
        for (int j = 0; j < i; ++j)
            sum += abs(points[j].first - points[i].first) + abs(points[j].second - points[i].second);
    cout << sum << endl;
}

void partA() {
    solve(2);
}

void partB() {
    solve(1000000);
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