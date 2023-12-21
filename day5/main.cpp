#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct MapRange {
    ll dst_start;
    ll src_start;
    ll size;
};

void partA() {
    string line;

    // seeds
    getline(cin, line);
    vector<ll> vals;
    for (int i = 6; i < line.size(); ++i) {
        if (line[i] == ' ') {
            vals.push_back(0);
            continue;
        }
        vals.back() = vals.back() * 10 + (line[i] - '0');
    }
    cin.ignore(1000, '\n');
    cin.ignore(1000, '\n');

    // mappings
    vector<MapRange> ranges;
    auto handle_mapping = [&]() {
        sort(ranges.begin(), ranges.end(), [](MapRange& a, MapRange& b) {
            return a.src_start < b.src_start;
        });
        for (ll& v : vals) {
            int l = 0;
            int r = ranges.size() - 1;
            while (l != r) {
                int m = (l + r + 1) >> 1;
                if (ranges[m].src_start <= v)
                    l = m;
                else
                    r = m-1;
            }
            int offset = v - ranges[l].src_start;
            if (offset >= 0 && offset < ranges[l].size)
                v = ranges[l].dst_start + offset;
        }
        ranges.clear();
    };
    while (getline(cin, line)) {
        if (line.empty()) {
            handle_mapping();
            cin.ignore(1000, '\n');
            continue;
        }
        ranges.emplace_back();
        MapRange& r = ranges.back();
        r.dst_start = 0;
        int i;
        for (i = 0; line[i] != ' '; ++i)
            r.dst_start = r.dst_start * 10 + (line[i] - '0');
        r.src_start = 0;
        for (++i; line[i] != ' '; ++i)
            r.src_start = r.src_start * 10 + (line[i] - '0');
        r.size = 0;
        for (++i; i < line.size(); ++i)
            r.size = r.size * 10 + (line[i] - '0');
    }
    handle_mapping();
    ll min_val = vals[0];
    for (int i = 1; i < vals.size(); ++i)
        min_val = min(min_val, vals[i]);
    cout << min_val << endl;
}

void partB() {
    string line;

    // seeds
    getline(cin, line);
    vector<ll> vals;
    for (int i = 6; i < line.size(); ++i) {
        if (line[i] == ' ') {
            vals.push_back(0);
            continue;
        }
        vals.back() = vals.back() * 10 + (line[i] - '0');
    }
    vector<pair<ll,ll>> itvs;
    for (int i = 0; i < vals.size(); i += 2)
        itvs.emplace_back(vals[i], vals[i] + vals[i+1] - 1);
    cin.ignore(1000, '\n');
    cin.ignore(1000, '\n');

    // mappings
    vector<MapRange> ranges;
    auto handle_mapping = [&]() {
        sort(ranges.begin(), ranges.end(), [](MapRange& a, MapRange& b) {
            return a.src_start < b.src_start;
        });
        sort(itvs.begin(), itvs.end(), [](pair<ll,ll>& a, pair<ll,ll>& b) {
            return a.first < b.first;
        });
        int ri = 0;
        vector<pair<ll,ll>> new_itvs;
        for (pair<ll,ll>& x : itvs) {
            auto move_to = [&](ll pos) {
                while (ri < ranges.size() && ranges[ri].src_start + ranges[ri].size <= pos) ++ri;
            };
            ll pos = x.first;
            while (pos <= x.second) {
                move_to(pos);
                if (ri == ranges.size()) {
                    new_itvs.emplace_back(pos, x.second);
                    break;
                }
                if (ranges[ri].src_start > pos) {
                    ll end = min(x.second, ranges[ri].src_start);
                    assert(end >= pos);
                    new_itvs.emplace_back(pos, end);
                    pos = end + 1;
                    continue;
                }
                ll end = min(x.second, ranges[ri].src_start + ranges[ri].size - 1);
                assert(end >= pos);
                new_itvs.emplace_back(pos - ranges[ri].src_start + ranges[ri].dst_start, end - ranges[ri].src_start + ranges[ri].dst_start);
                pos = end + 1;
            }
        }
        itvs = move(new_itvs);
        ranges.clear();
    };
    while (getline(cin, line)) {
        if (line.empty()) {
            handle_mapping();
            cin.ignore(1000, '\n');
            continue;
        }
        ranges.emplace_back();
        MapRange& r = ranges.back();
        r.dst_start = 0;
        int i;
        for (i = 0; line[i] != ' '; ++i)
            r.dst_start = r.dst_start * 10 + (line[i] - '0');
        r.src_start = 0;
        for (++i; line[i] != ' '; ++i)
            r.src_start = r.src_start * 10 + (line[i] - '0');
        r.size = 0;
        for (++i; i < line.size(); ++i)
            r.size = r.size * 10 + (line[i] - '0');
    }
    handle_mapping();
    ll min_val = LLONG_MAX;
    for (auto& x : itvs)
        min_val = min(min_val, x.first);
    cout << min_val << endl;
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