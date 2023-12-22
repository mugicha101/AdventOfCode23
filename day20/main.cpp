#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void partA() {
    string line;
    vector<vector<int>> adj;
    vector<int> inDeg;
    vector<char> gate;
    vector<int> gateData;
    vector<pair<unordered_map<int,bool>,int>> conjHist;
    unordered_map<string, int> nodeMap;
    auto nodeId = [&](string label) {
        auto it = nodeMap.find(label);
        if (it != nodeMap.end()) return it->second;
        adj.emplace_back();
        gate.emplace_back();
        gateData.emplace_back();
        inDeg.emplace_back();
        nodeMap[label] = (int)nodeMap.size();
        return (int)nodeMap.size()-1;
    };
    while (getline(cin, line)) {
        int split = line.find(' ');
        int src = nodeId(line.substr(1, split-1));
        gate[src] = line[0];
        if (gate[src] == '&') {
            gateData[src] = conjHist.size();
            conjHist.emplace_back();
        }
        line.push_back(',');
        int start = split + 4;
        for (int i = start + 1; i < line.size(); ++i) {
            if (line[i] == ',') {
                int dst = nodeId(line.substr(start, i - start));
                ++inDeg[dst];
                adj[src].push_back(dst);
                start = i + 2;
                i = start;
            }
        }
    }
    queue<tuple<int,int,bool>> q;
    ll numLow = 1000, numHigh = 0;
    for (int p = 0; p < 1000; ++p) {
        q.emplace(-1, nodeMap["roadcaster"], false);
        while (!q.empty()) {
            auto [src, dst, sig] = q.front();
            q.pop();
            if (gate[dst] == '%') {
                if (sig) continue;
                sig = gateData[dst] = 1 - gateData[dst];
            } else if (gate[dst] == '&') {
                auto& [hist, highs] = conjHist[gateData[dst]];
                bool& h = hist[src];
                if (sig) highs += !h;
                else highs -= h;
                h = sig;
                sig = highs != inDeg[dst];
            }
            (sig ? numHigh : numLow) += adj[dst].size();
            for (int next : adj[dst])
                q.emplace(dst, next, sig);
        }
    }
    cout << numLow * numHigh << endl;
}

void partB() {
    string line;
    vector<vector<int>> adj;
    vector<vector<int>> rev;
    vector<char> gate;
    vector<int> gateData;
    vector<string> labels;
    vector<pair<unordered_map<int,bool>,int>> conjHist;
    unordered_map<string, int> nodeMap;
    auto nodeId = [&](string label) {
        auto it = nodeMap.find(label);
        if (it != nodeMap.end()) return it->second;
        adj.emplace_back();
        rev.emplace_back();
        gate.emplace_back();
        gateData.emplace_back();
        labels.push_back(label);
        nodeMap[label] = (int)nodeMap.size();
        return (int)nodeMap.size()-1;
    };
    while (getline(cin, line)) {
        int split = line.find(' ');
        int src = nodeId(line.substr(1, split-1));
        gate[src] = line[0];
        if (gate[src] == '&') {
            gateData[src] = conjHist.size();
            conjHist.emplace_back();
        }
        line.push_back(',');
        int start = split + 4;
        for (int i = start + 1; i < line.size(); ++i) {
            if (line[i] == ',') {
                int dst = nodeId(line.substr(start, i - start));
                adj[src].push_back(dst);
                rev[dst].push_back(src);
                start = i + 2;
                i = start;
            }
        }
    }

    // assume periodic inputs to rx
    int rx = nodeMap["rx"];
    int rxParent = rev[rx][0];
    queue<tuple<int,int,bool>> q;
    bool done = false;
    int presses = 0;
    vector<int> firstHighSent(adj.size(), -1);
    while (!done) {
        ++presses;
        q.emplace(-1, nodeMap["roadcaster"], false);
        while (!q.empty()) {
            auto [src, dst, sig] = q.front();
            q.pop();
            if (gate[dst] == '%') {
                if (sig) continue;
                sig = gateData[dst] = 1 - gateData[dst];
            } else if (gate[dst] == '&') {
                auto& [hist, highs] = conjHist[gateData[dst]];
                bool& h = hist[src];
                if (sig) highs += !h;
                else highs -= h;
                h = sig;
                sig = highs != rev[dst].size();
            }
            if (sig && firstHighSent[dst] == -1) firstHighSent[dst] = presses;
            for (int next : adj[dst])
                q.emplace(dst, next, sig);
        }
        done = true;
        for (int keyNode : rev[rxParent]) {
            if (firstHighSent[keyNode] == -1) {
                done = false;
                break;
            }
        }
    }
    ll res = 1;
    for (int keyNode : rev[rxParent])
        res = lcm(res, (ll)firstHighSent[keyNode]);
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