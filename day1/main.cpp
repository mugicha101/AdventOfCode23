#include <bits/stdc++.h>

using namespace std;

void partA() {
    string s;
    int sum = 0;
    while (getline(cin, s)) {
        int first, last;
        auto isDig = [](char c) {
            return c >= '0' && c <= '9';
        };
        for (first = 0; !isDig(s[first]); ++first);
        for (last = s.size()-1; !isDig(s[last]); --last);
        sum += (s[first]-'0') * 10 + (s[last]-'0');
    }
    cout << sum << endl;
}

void partB() {
    // could use a trie or zarr but eh
    string s;
    int sum = 0;
    const string digs[9] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    while (getline(cin, s)) {
        int index[9];
        int first_val = -1, last_val = -1;
        for (int i = 0; first_val == -1; ++i) {
            char c = s[i];
            if (c >= '0' && c <= '9') {
                first_val = c-'0';
                continue;
            }
            for (int d = 0; d < 9; ++d) {
                if (s.size() - i < digs[d].size() || s.substr(i, digs[d].size()) != digs[d])
                    continue;
                first_val = d+1;
            }
        }
        for (int i = s.size()-1; last_val == -1; --i) {
            char c = s[i];
            if (c >= '0' && c <= '9') {
                last_val = c-'0';
                continue;
            }
            for (int d = 0; d < 9; ++d) {
                if (s.size() - i < digs[d].size() || s.substr(i, digs[d].size()) != digs[d])
                    continue;
                last_val = d+1;
            }
        }
        sum += first_val * 10 + last_val;
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
    cout << chrono::duration_cast<chrono::microseconds>(end - start).count() << "microseconds" << endl;
}