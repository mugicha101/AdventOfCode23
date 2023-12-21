#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll calcWays(long double t, long double d) {
    // h * (t - h) >= d
    // h * t - h^2 = d
    // -1 * h^2 + t * h - d = 0
    // h^2 - t * h + d = 0
    // (t +- sqrt(t^2 - 4d)) / 2
    long double left = t * 0.5;
    long double right = sqrt(left * left - d);
    long double low = left - right;
    long double high = left + right;
    return (ll)ceil(high) - (ll)floor(low) - 1;
}

void partA() {
    string line;
    auto read_line = [&]() {
        getline(cin, line);
        line.push_back(' ');
        bool num = false;
        vector<int> vals;
        for (int i = 9; i < line.size(); ++i) {
            if (line[i] == ' ') {
                num = false;
                continue;
            }
            if (!num) {
                vals.push_back(0);
                num = true;
            }
            vals.back() = vals.back() * 10 + (line[i] - '0');
        }
        return vals;
    };
    vector<int> times = read_line();
    vector<int> dists = read_line();
    int races = times.size();
    ll prod = 1;
    for (int r = 0; r < races; ++r)
        prod *= calcWays(times[r], dists[r]);
    cout << prod << endl;
}

void partB() {
    string line;
    auto read_line = [&]() {
        getline(cin, line);
        ll val = 0;
        for (int i = 9; i < line.size(); ++i) {
            if (line[i] == ' ')
                continue;
            val = val * 10 + (line[i] - '0');
        }
        return val;
    };
    ll t = read_line();
    ll d = read_line();
    cout << calcWays(t, d) << endl;
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