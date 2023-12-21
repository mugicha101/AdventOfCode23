#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Card {
    int val;
    int bid;
};

void partA() {
    string line;
    vector<Card> cards; // value, bid
    char syms[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    char symStr[256];
    for (int i = 0; i < 13; ++i)
        symStr[syms[i]] = i;
    while (getline(cin, line)) {
        cards.emplace_back();
        int& bid = cards.back().bid;
        int& val = cards.back().val;
        bid = 0;
        val = 0;
        for (int i = 6; i < line.size(); ++i)
            bid = bid * 10 + (line[i] - '0');
        unordered_map<char,int> count;
        for (int i = 0; i < 5; ++i) {
            ++count[line[i]];
            val = (val << 4) | symStr[line[i]];
        }
        int kindType = 1;
        int pairs = 0;
        for (auto& p : count) {
            kindType = max(kindType, p.second);
            pairs += p.second == 2;
        }
        if (kindType >= 4) val |= (kindType + 1) << 20;
        else if (kindType == 3) val |= (3 + pairs) << 20;
        else val |= pairs << 20;
    }
    sort(cards.begin(), cards.end(), [](auto& a, auto& b) {
        return a.val > b.val;
    });
    long long adder = 0;
    long long res = 0;
    for (int i = 0; i < cards.size(); ++i) {
        adder += cards[i].bid;
        res += adder;
    }
    cout << res << endl;
}

void partB() {
    string line;
    vector<Card> cards; // value, bid
    char syms[] = {'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};
    char symStr[256];
    for (int i = 0; i < 13; ++i)
        symStr[syms[i]] = i;
    while (getline(cin, line)) {
        cards.emplace_back();
        int& bid = cards.back().bid;
        int& val = cards.back().val;
        bid = 0;
        val = 0;
        for (int i = 6; i < line.size(); ++i)
            bid = bid * 10 + (line[i] - '0');
        unordered_map<char,int> count;
        for (int i = 0; i < 5; ++i) {
            ++count[line[i]];
            val = (val << 4) | symStr[line[i]];
        }
        int kindType = 0;
        int pairs = 0;
        int jokers = count['J'];
        count.erase('J');
        for (auto& p : count) {
            kindType = max(kindType, p.second);
            pairs += p.second == 2;
        }
        if (kindType + jokers >= 4) val |= (kindType + jokers + 1) << 20;
        else if (kindType == 3) val |= (3 + pairs) << 20;
        else if (kindType == 2 && jokers) val |= (3 + pairs - 1) << 20;
        else if (kindType + jokers == 3) val |= 3 << 20;
        else val |= (pairs + jokers) << 20;
    }
    sort(cards.begin(), cards.end(), [](auto& a, auto& b) {
        return a.val > b.val;
    });
    long long adder = 0;
    long long res = 0;
    for (int i = 0; i < cards.size(); ++i) {
        adder += cards[i].bid;
        res += adder;
    }
    cout << res << endl;
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