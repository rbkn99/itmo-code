//
// Created by matveich on 29.05.18.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

typedef unsigned int ui;

set<int> accepting_states;
vector<map<char, set<int> > > edges;
map<string, int> encoded;
int start;

bool accepts(string &word) {
    set<int> curr, prev;
    prev.insert(start);
    for (char c: word) {
        for (auto x: prev) {
            for (auto to: edges[x][c]) {
                curr.insert(to);
            }
        }
        prev = curr;
        curr.clear();
    }
    for (auto x: prev) {
        if (accepting_states.find(x) != accepting_states.end())
            return true;
    }
    return false;
}

ui n;

int main() {
    freopen("automaton.in", "r", stdin);
    freopen("automaton.out", "w", stdout);
    ios::sync_with_stdio(false);
    string str_start;
    cin >> n >> str_start;
    edges.resize(27);
    accepting_states.insert(26);
    string tmp, tmp1;
    int c = 0;

    for (int i = 0; i < n; i++) {
        cin >> tmp >> tmp1 >> tmp1;
        if (encoded.count(tmp) == 0)
            encoded[tmp] = c++;
        if (tmp1.size() == 1) {
            edges[encoded[tmp]][tmp1[0]].insert(26);
        }
        else {
            auto s = string(1, tmp1[1]);
            if (encoded.count(s) == 0)
                encoded[s] = c++;
            edges[encoded[tmp]][tmp1[0]].insert(encoded[s]);
        }
    }
    start = encoded[str_start];
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> tmp;
        cout << (accepts(tmp) ? "yes\n": "no\n");
    }
    return 0;
}
