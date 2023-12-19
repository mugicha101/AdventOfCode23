#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void part(bool partB) {
    string line;
    ll sum = 0;
    while (getline(cin, line)) {
        ll val = 0;
        bool neg = false;
        vector<vector<ll>> vals(1);
        line.push_back(' ');
        for (char c : line) {
            if (c == ' ') {
                vals[0].push_back(neg ? -val : val);
                val = 0;
                neg = false;
            } else if (c == '-')
                neg = true;
            else
                val = val * 10 + (c - '0');
        }
        ll m = 1;
        while (m != 0) {
            vals.emplace_back();
            vector<ll>& prev = vals[vals.size()-2];
            vector<ll>& curr = vals[vals.size()-1];
            curr.reserve(prev.size()-1);
            m = 0;
            for (int i = 1; i < prev.size(); ++i) {
                curr.emplace_back(prev[i] - prev[i-1]);
                m |= curr.back();
            }
        }
        ll v = 0;
        for (int row = vals.size()-2; row >= 0; --row)
            v = partB ? vals[row].front() - v : vals[row].back() + v;
        sum += v;
    }
    cout << sum << endl;
}

void partA() {
    part(false);
}

void partB() {
    part(true);
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