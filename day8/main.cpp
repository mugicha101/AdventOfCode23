#include <bits/stdc++.h>

using namespace std;

void partA() {
    string line;
    getline(cin, line);
    vector<bool> moves;
    moves.reserve(line.size());
    for (char c : line) moves.push_back(c == 'R');
    cin.ignore(1000, '\n');
    vector<pair<int,int>> adj;
    unordered_map<int,int> nids;
    while (getline(cin, line)) {
        auto getId = [&](int i) {
            int id = ((int)line[i] - 'A') * 676 + ((int)line[i+1] - 'A') * 26 + ((int)line[i+2] - 'A');
            auto it = nids.find(id);
            if (it != nids.end()) return it->second;
            adj.emplace_back();
            return nids[id] = nids.size();
        };
        adj[getId(0)] = make_pair(getId(7), getId(12));
    }
    int steps = 0;
    int target = nids[17575];
    int curr = nids[0];
    while (curr != target)
        curr = moves[(steps++) % moves.size()] ? adj[curr].second : adj[curr].first;
    cout << steps << endl;
}

void partB() {
    string line;
    getline(cin, line);
    vector<bool> moves;
    moves.reserve(line.size());
    for (char c : line) moves.push_back(c == 'R');
    cin.ignore(1000, '\n');
    vector<pair<int,int>> adj;
    vector<bool> isEnd;
    unordered_map<int,int> nids;
    vector<int> positions;
    while (getline(cin, line)) {
        auto getId = [&](int i) {
            int id = ((int)line[i] - 'A') * 676 + ((int)line[i+1] - 'A') * 26 + ((int)line[i+2] - 'A');
            auto it = nids.find(id);
            if (it != nids.end()) return it->second;
            adj.emplace_back();
            if (line[i+2] == 'A') positions.push_back(nids.size());
            isEnd.push_back(line[i+2] == 'Z');
            return nids[id] = nids.size();
        };
        adj[getId(0)] = make_pair(getId(7), getId(12));
    }
    long long lcmv = 1;
    for (int i = 0; i < positions.size(); ++i) {
        int ending = -1;
        map<pair<int,int>,int> visited;
        int steps = 0;
        pair<int,int> state = make_pair(positions[i], 0);
        auto& [p, m] = state;
        while (!visited.count(state)) {
            visited[state] = steps;
            if (isEnd[p]) ending = steps;
            p = moves[m] ? adj[p].second : adj[p].first;
            ++steps;
            m = m + 1 == moves.size() ? 0 : m + 1;
        }
        lcmv = lcm(lcmv, steps - visited[state]);
    }
    cout << lcmv << endl;
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