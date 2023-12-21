#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll calcWays(string& line, vector<int>& seqs) {
    // valid ways to form sequence starting from each . or ?
    int numPos = line.size();
    int numSeqs = seqs.size();
    line.push_back('.');
    vector<unordered_set<int>> seqOptions(numPos);
    char prev = '.';
    for (int p = 0; p < numPos; prev = line[p++]) {
        if (prev == '#') continue;
        for (int i = p; line[i] != '.'; ++i) {
            if (line[i+1] != '#')
                seqOptions[p].insert(i+1-p);
        }
    }

    // state = seq index, pos
    // only need prev seq index, so 1D
    vector<vector<ll>> ways(2, vector<ll>(numPos+2));
    ways[0][0] = 1;
    for (int s = 0; s < numSeqs; ++s) {
        int o = s & 1;
        int seqLen = seqs[s];
        memset(&ways[1-o][0], 0, (numPos+2) * sizeof(ll));
        for (int p = 0; p <= numPos; ++p) {
            if (line[p] != '#') ways[o][p+1] += ways[o][p];
            if (line[p] != '.' && seqOptions[p].count(seqLen)) ways[1-o][p+seqLen+1] += ways[o][p];
        }
    }
    for (int p = 0; p <= numPos; ++p)
        if (line[p] != '#') ways[numSeqs & 1][p+1] += ways[numSeqs & 1][p];
    return ways[numSeqs & 1][numPos+1];
}

void solve(int repeats) {
    string line;
    long long sum = 0;
    while (getline(cin, line)) {
        int numPos = line.find(' ');
        vector<int> seqs(1, 0);
        for (int i = numPos+1; i < line.size(); ++i) {
            if (line[i] == ',')
                seqs.push_back(0);
            else
                seqs.back() = seqs.back() * 10 + (line[i] - '0');
        }
        line = line.substr(0, numPos);
        string calcLine = line;
        vector<int> calcSeqs = seqs;
        calcSeqs.reserve(seqs.size() * (repeats + 1));
        for (int i = 0; i < repeats; ++i) {
            calcLine += '?';
            calcLine += line;
            calcSeqs.insert(calcSeqs.end(), seqs.begin(), seqs.end());
        }
        sum += calcWays(calcLine, calcSeqs);
    }
    cout << sum << endl;
}

void partA() {
    solve(0);
}

void partB() {
    solve(4);
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