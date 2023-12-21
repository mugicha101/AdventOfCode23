#include <bits/stdc++.h>

using namespace std;

char varmap[256];

void init() {
    varmap['x'] = 0;
    varmap['m'] = 1;
    varmap['a'] = 2;
    varmap['s'] = 3;
}

struct Condition {
    char op;
    char var;
    int val;
    string dest;
    bool match(int vars[]) {
        if (op == '<') return vars[var] < val;
        if (op == '>') return vars[var] > val;
        return true;
    }
};


void workflowInput(unordered_map<string, vector<Condition>>& workflows) {
    string line;
    while (getline(cin, line) && !line.empty()) {
        line.back() = ',';
        int i = line.find('{');
        string label = line.substr(0, i);
        vector<Condition>& workflow = workflows[label];
        int start = i+1;
        int split = -1;
        int op = -1;
        for (++i; i < line.size(); ++i) {
            switch (line[i]) {
                case ',': {
                    workflow.emplace_back();
                    Condition& cond = workflow.back();
                    if (split == -1) {
                        cond.dest = line.substr(start, i-start);
                        cond.op = ' ';
                    } else {
                        cond.dest = line.substr(split+1, i-split-1);
                        cond.op = line[op];
                        cond.var = varmap[line[start]];
                        cond.val = 0;
                        for (int j = op+1; j < split; ++j)
                            cond.val = cond.val * 10 + (line[j] - '0');
                    }
                    split = -1;
                    start = i+1;
                } break;
                case '<':
                case '>':
                    op = i;
                    break;
                case ':':
                    split = i;
                    break;
            }
        }
    }
}

void partA() {
    string line;
    init();
    unordered_map<string, vector<Condition>> workflows;
    workflowInput(workflows);
    int sum = 0;
    while (getline(cin, line)) {
        int delims[] = {(int)line.find('x'), (int)line.find('m'), (int)line.find('a'), (int)line.find('s'), (int)line.size()};
        int vars[4] = {0,0,0,0};
        for (int i = 0; i < 4; ++i)
            for (int j = delims[i]+2; j < delims[i+1]-1; ++j)
                vars[i] = vars[i] * 10 + (line[j] - '0');
        string label = "in";
        while (label != "A" && label != "R") {
            vector<Condition>& workflow = workflows[label];
            int i = 0;
            while (!workflow[i].match(vars)) ++i;
            label = workflow[i].dest;
        }
        if (label != "A") continue;
        sum += vars[0] + vars[1] + vars[2] + vars[3];
    }
    cout << sum << endl;
}

long long dfs(unordered_map<string, vector<Condition>> workflows, string label, int varMin[4], int varMax[4]) {
    long long sum = 0;
    if (label == "R")
        return 0;
    if (label == "A") {
        sum = 1;
        for (int i = 0; i < 4; ++i)
            sum *= varMax[i] + 1 - varMin[i];
        return sum;
    }
    vector<Condition>& workflow = workflows[label];
    int initMin[4]; int initMax[4];
    memcpy(initMin, varMin, 4 << 2);
    memcpy(initMax, varMax, 4 << 2);
    for (Condition& cond : workflow) {
        if (cond.op == ' ') {
            sum += dfs(workflows, cond.dest, varMin, varMax);
            break;
        }
        if (cond.op == '>') {
            int old = varMin[cond.var];
            varMin[cond.var] = max(varMin[cond.var], cond.val + 1);
            if (varMin[cond.var] <= varMax[cond.var])
                sum += dfs(workflows, cond.dest, varMin, varMax);
            varMin[cond.var] = old;
            varMax[cond.var] = min(varMax[cond.var], cond.val);
        } else {
            int old = varMax[cond.var];
            varMax[cond.var] = min(varMax[cond.var], cond.val - 1);
            if (varMin[cond.var] <= varMax[cond.var])
                sum += dfs(workflows, cond.dest, varMin, varMax);
            varMax[cond.var] = old;
            varMin[cond.var] = max(varMin[cond.var], cond.val);
        }
        if (varMin[cond.var] > varMax[cond.var])
            break;
    }
    memcpy(varMin, initMin, 4 << 2);
    memcpy(varMax, initMax, 4 << 2);
    return sum;
}

void partB() {
    string line;
    init();
    unordered_map<string, vector<Condition>> workflows;
    workflowInput(workflows);
    int varMin[] = {1,1,1,1};
    int varMax[] = {4000,4000,4000,4000};
    cout << dfs(workflows, "in", varMin, varMax) << endl;
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