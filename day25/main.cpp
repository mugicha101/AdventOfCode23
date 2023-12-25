#include <bits/stdc++.h>

using namespace std;

int source, sink;
bool ff(vector<unordered_map<int, int8_t>>& adj, vector<bool>& visited, vector<int>& path, int node, int8_t bottleneck) {
    if (node == sink) {
        path.push_back(node);
        for (int i = 1; i < path.size(); ++i) {
            adj[path[i-1]][path[i]] += bottleneck;
            adj[path[i]][path[i-1]] -= bottleneck;
        }
        path.pop_back();
        return true;
    }
    visited[node] = true;
    path.push_back(node);
    bool ret = false;

    for (auto& [next, flow] : adj[node]) {
        if (visited[next] || flow == 1) continue;
        ret = ff(adj, visited, path, next, min(bottleneck, (int8_t)(1-flow)));
        if (ret) break;
    }

    path.pop_back();
    return ret;
}

void reach(vector<unordered_map<int, int8_t>>& adj, vector<bool>& visited, int node) {
    visited[node] = true;
    for (auto& [next, flow] : adj[node]) {
        if (visited[next] || flow == 1) continue;
        reach(adj, visited, next);
    }
}

void partA() {
    string line;
    unordered_map<int,int> idMap;
    vector<unordered_map<int, int8_t>> adj;
    vector<string> labels;
    auto getId = [&](int i) {
        int val = ((int)(line[i]-'a') << 10) | ((int)(line[i+1]-'a') << 5) | (int)(line[i+2]-'a');
        auto it = idMap.find(val);
        if (it != idMap.end())
            return it->second;
        idMap[val] = idMap.size();
        adj.emplace_back();
        labels.push_back(line.substr(i, 3));
        return (int)idMap.size()-1;
    };
    while (getline(cin, line)) {
        int a = getId(0);
        for (int i = 5; i < line.size(); i += 4) {
            int b = getId(i);
            adj[a][b] = 0;
            adj[b][a] = 0;
        }
    }

    // pick random nodes until max flow from a to b = 3, then find min cut
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<int> path;
    srand(time(NULL));
    while (true) {
        source = rand() % n;
        sink = rand() % n;
        if (source == sink) continue;

        // reset graph O(V)
        for (auto& row : adj)
            for (auto& kvp : row)
                kvp.second = 0;

        // ford fulkerson
        int attempts = 0;
        for (int i = 0; i < n; ++i) visited[i] = false;
        while (ff(adj, visited, path, source, 2)) {
            for (int i = 0; i < n; ++i) visited[i] = false;
        }
        int outFlow = 0;
        for (auto& [nb, flow] : adj[sink])
            outFlow += adj[nb][sink];
        if (outFlow == 3) break;
    }

    // calc min cut
    reach(adj, visited, source);
    int s = 0;
    for (bool b : visited)
        s += b;
    int result = s * (n-s);
    cout << result << endl;
}

void partB() {
    string line;
    while (getline(cin, line)) {
        
    }
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