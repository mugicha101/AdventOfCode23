#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int8_t dx[256];
int8_t dy[256];
int8_t hexmap[256];

void init() {
    dx['0'] = dx['R'] = 1;
    dy['0'] = dy['R'] = 0;
    dx['1'] = dx['D'] = 0;
    dy['1'] = dy['D'] = -1;
    dx['2'] = dx['L'] = -1;
    dy['2'] = dy['L'] = 0;
    dx['3'] = dx['U'] = 0;
    dy['3'] = dy['U'] = 1;
    for (int i = 0; i < 10; ++i)
        hexmap['0' + i] = i;
    for (int i = 0; i < 6; ++i)
        hexmap['a' + i] = 10 + i;
}

void solve(function<pair<char,ll>(string&)> parseLine) {
    init();
    string line;
    ll area = 0;
    ll perimeter = 0;
    ll x = 0, y = 0;
    while (getline(cin, line)) {
        auto [dir, amt] = parseLine(line);
        ll nx = x + (ll)dx[dir] * amt;
        ll ny = y + (ll)dy[dir] * amt;
        perimeter += amt;
        area += x * ny - y * nx; // shoelace
        x = nx; y = ny;
    }
    // area = shoelace area + perimeter * 0.5 (for added perimeter) + 1 (for corner sums)
    area = ((abs(area) + perimeter) >> 1) + 1;
    cout << area << endl;
}

void partA() {
    solve([](string& line) {
        ll amt = 0;
        for (int i = 2; line[i] != ' '; ++i)
            amt = amt * 10 + (line[i] - '0');
        return make_pair(line[0], amt);
    });
}

void partB() {
    solve([](string& line) {
        ll amt = 0;
        for (int i = line.size() - 7; i < line.size() - 2; ++i)
            amt = (amt << 4) | hexmap[line[i]];
        return make_pair(line[line.size() - 2], amt);
    });
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