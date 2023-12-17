#include <bits/stdc++.h>

using namespace std;

void partA() {
    string line;
    char line_num = 0;
    char vals[100];
    memset(vals, 0, 100);
    int sum = 0;
    while (getline(cin, line)) {
        ++line_num;
        int i = 5;
        for (; line[i] != ':'; ++i);
        for (i += 2; line[i] != '|'; i += 3)
            vals[(line[i] == ' ' ? 0 : (int)(line[i] - '0')) * 10 + (line[i+1] - '0')] = line_num;
        int count = 0;
        for (i += 2; i < line.size(); i += 3)
            count += vals[(line[i] == ' ' ? 0 : (int)(line[i] - '0')) * 10 + (line[i+1] - '0')] == line_num;
        sum += count ? (1 << (count - 1)) : 0;
    }
    cout << sum << endl;
}

void partB() {
    string line;
    char line_num = 0;
    char vals[100];
    memset(vals, 0, 100);
    vector<int> counts;
    while (getline(cin, line)) {
        ++line_num;
        int i = 5;
        for (; line[i] != ':'; ++i);
        for (i += 2; line[i] != '|'; i += 3)
            vals[(line[i] == ' ' ? 0 : (int)(line[i] - '0')) * 10 + (line[i+1] - '0')] = line_num;
        int count = 0;
        for (i += 2; i < line.size(); i += 3)
            count += vals[(line[i] == ' ' ? 0 : (int)(line[i] - '0')) * 10 + (line[i+1] - '0')] == line_num;
        counts.push_back(count);
    }
    int sum = 0;
    int cards = counts.size();
    vector<int> change(cards, 0);
    int instances = 1;
    for (int i = 0; i < cards; ++i) {
        sum += instances;
        if (i + counts[i] < cards) change[i + counts[i]] += instances;
        instances <<= 1;
        instances -= change[i];
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