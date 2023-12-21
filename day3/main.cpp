#include <bits/stdc++.h>

using namespace std;

void partA() {
    int sum = 0;
    string prev;
    string curr;
    string next;
    int line_size;
    auto read_line = [&]() {
        if (!getline(cin, next)) return false;
        for (char& c : next) {
            if (c != '.' && (c < '0' || c > '9'))
                c = '*';
        }
        next.push_back('.');
        return true;
    };
    auto step = [&]() {
        swap(prev, curr);
        swap(curr, next);
    };
    auto handle = [&]() {
        bool nb = false;
        int val = -1;
        for (int i = 0; i < line_size; ++i) {
            char c = curr[i];
            bool d = c >= '0' && c <= '9';
            if (d && val == -1) { // begin label
                nb = i && (prev[i-1] == '*' || curr[i-1] == '*' || next[i-1] == '*');
                val = 0;
            } else if (!d && val != -1) { // end label
                nb = nb || prev[i] == '*' || curr[i] == '*' || next[i] == '*';
                if (nb)
                    sum += val;
                val = -1;
            }
            if (val == -1) continue;
            val = val * 10 + (c - '0');
            nb = nb || prev[i] == '*' || curr[i] == '*' || next[i] == '*';
        }
    };
    read_line();
    line_size = next.size();
    prev.resize(line_size, '.');
    curr.resize(line_size, '.');
    step();
    while (read_line()) {
        handle();
        step();
    }
    next = string(line_size, '.');
    handle();
    cout << sum << endl;
}

void partB() {
    int sum = 0;
    string prev;
    string curr;
    string next;
    int line_size;
    unordered_map<int, pair<int,int>> gear_data; // position -> adjacent label count, first label
    auto read_line = [&]() {
        if (!getline(cin, next)) return false;
        for (char& c : next) {
            if (c != '.' && c != '*' && (c < '0' || c > '9'))
                c = '.';
        }
        next.push_back('.');
        return true;
    };
    auto step = [&]() {
        swap(prev, curr);
        swap(curr, next);
    };
    int pos_offset = 0;
    auto handle = [&]() {
        int val = -1;
        vector<int> gears;
        for (int i = 0; i < line_size; ++i) {
            char c = curr[i];
            bool d = c >= '0' && c <= '9';
            auto find_gears = [&](int index) {
                int pos = pos_offset + index;
                if (prev[index] == '*') gears.push_back(pos - line_size);
                if (curr[index] == '*') gears.push_back(pos);
                if (next[index] == '*') gears.push_back(pos + line_size);
            };
            if (d && val == -1) { // begin label
                val = 0;
                gears.clear();
                if (i) find_gears(i-1);
            } else if (!d && val != -1) { // end label
                find_gears(i);
                for (int p : gears) {
                    auto& g = gear_data[p];
                    if (++g.first == 1)
                        g.second = val;
                    else if (g.first == 2)
                        sum += g.second * val;
                }
                val = -1;
            }
            if (val == -1) continue;
            val = val * 10 + (c - '0');
            find_gears(i);
        }
        pos_offset += line_size;
    };
    read_line();
    line_size = next.size();
    prev.resize(line_size, '.');
    curr.resize(line_size, '.');
    step();
    while (read_line()) {
        handle();
        step();
    }
    next = string(line_size, '.');
    handle();
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