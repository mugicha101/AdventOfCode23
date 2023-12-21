#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void partA() {
    string line;
    getline(cin, line);
    line.push_back(',');
    int sum = 0;
    int val = 0;
    for (char c : line) {
        if (c == ',') {
            sum += val;
            val = 0;
            continue;
        }
        val = ((val + c) * 17) & 0xff;
    }
    cout << sum << endl;
}

class Box {
    int nextPos = 0;
    unordered_map<string,pair<int,int>> data; // label -> pos, focal
public:
    void remove(string label) {
        data.erase(label);
    }

    void add(string label, int focal) {
        auto it = data.find(label);
        if (it != data.end()) {
            it->second.second = focal;
            return;
        }
        data[label] = make_pair(nextPos++, focal);
    }

    vector<pair<int,int>> dump() {
        vector<pair<int,int>> dumpData;
        dumpData.reserve(data.size());
        for (auto& kvp : data) dumpData.push_back(kvp.second);
        sort(dumpData.begin(), dumpData.end(), [](auto& a, auto& b) {
            return a.first < b.first;
        });
        for (int i = 0; i < dumpData.size(); ++i)
            dumpData[i].first = i;
        return dumpData;
    }
};

void partB() {
    string line;
    getline(cin, line);
    line.push_back(',');
    int start = 0;
    int op = -1;
    Box boxes[256];
    for (int i = 0; i < 256; ++i) boxes[i] = Box();
    auto handleB = [&](int start, int end) {
        string label = line.substr(start, op-start);
        int hash = 0;
        for (int i = start; i < op; ++i) hash = ((hash + line[i]) * 17) & 0xff;
        if (line[op] == '-')
            boxes[hash].remove(label);
        else
            boxes[hash].add(label, line[end-1] - '0');
    };
    for (int i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == ',') {
            handleB(start, i);
            start = i+1;
            op = -1;
            continue;
        }
        if (c == '-' || c == '=') op = i;
    }
    ll sum = 0;
    for (int i = 0; i < 256; ++i) {
        vector<pair<int,int>> data = boxes[i].dump();
        ll boxSum = 0;
        for (auto& p : data)
            boxSum += (ll)(p.first + 1) * (ll)p.second;
        sum += boxSum * (i + 1);
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
    cout << chrono::duration_cast<chrono::microseconds>(end - start).count() << "ms" << endl;
}