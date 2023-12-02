#include <bits/stdc++.h>

using namespace std;

void partA() {
    string s;
    int sum = 0;
    int game = 0;
    while (getline(cin, s)) {
        ++game;
        s.push_back(';');
        int round_start = 8 + (int)(game >= 10) + (int)(game >= 100);
        for (int round_end = round_start; round_end < s.size(); ++round_end) {
            if (s[round_end] != ';') continue;
            int hand_start = round_start;
            s[round_end] = ',';
            for (int hand_end = hand_start; hand_end <= round_end; ++hand_end) {
                if (s[hand_end] != ',') continue;
                int dig_end, cap;
                switch (s[hand_end-1]) {
                    case 'd': // RED
                        cap = 12;
                        dig_end = hand_end - 4;
                        break;
                    case 'n': // GREEN
                        cap = 13;
                        dig_end = hand_end - 6;
                        break;
                    case 'e': // BLUE
                        cap = 14;
                        dig_end = hand_end - 5;
                        break;
                    default:
                        exit(-1);
                }
                int amount = 0;
                for (int i = hand_start; i < dig_end; ++i) {
                    amount = amount * 10 + (s[i] - '0');
                }
                if (amount > cap) goto skip_game;
                hand_start = ++hand_end + 1;
            }
            round_start = ++round_end + 1;
        }
        sum += game;
        skip_game:;
    }
    cout << sum << endl;
}

void partB() {
    string s;
    int sum = 0;
    int game = 0;
    while (getline(cin, s)) {
        ++game;
        s.push_back(';');
        int round_start = 8 + (int)(game >= 10) + (int)(game >= 100);
        int min_balls[3] = {0, 0, 0};
        for (int round_end = round_start; round_end < s.size(); ++round_end) {
            if (s[round_end] != ';') continue;
            int hand_start = round_start;
            s[round_end] = ',';
            for (int hand_end = hand_start; hand_end <= round_end; ++hand_end) {
                if (s[hand_end] != ',') continue;
                int dig_end, type;
                switch (s[hand_end-1]) {
                    case 'd': // RED
                        type = 0;
                        dig_end = hand_end - 4;
                        break;
                    case 'n': // GREEN
                        type = 1;
                        dig_end = hand_end - 6;
                        break;
                    case 'e': // BLUE
                        type = 2;
                        dig_end = hand_end - 5;
                        break;
                    default:
                        exit(-1);
                }
                int amount = 0;
                for (int i = hand_start; i < dig_end; ++i) {
                    amount = amount * 10 + (s[i] - '0');
                }
                min_balls[type] = max(min_balls[type], amount);
                hand_start = ++hand_end + 1;
            }
            round_start = ++round_end + 1;
        }
        sum += min_balls[0] * min_balls[1] * min_balls[2];
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