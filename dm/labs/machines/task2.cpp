//
// Created by matveich on 07.05.18.
//

#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;

typedef unsigned int ui;

class NFSM {
public:

    NFSM() {
        start = 0;
        int n, m = 0, k = 0;
        scanf("%d%d%d", &n, &m, &k);
        int x, a = 0, b = 0;
        char c = ' ';
        for (int i = 0; i < k; i++) {
            scanf("%d", &x);
            accepting_states.insert(x - 1);
        }
        edges.resize((ui)n);
        for (int i = 0; i < m; i++) {
            scanf("%d%d%c%c", &a, &b, &c, &c);
            edges[a - 1][c].insert(b - 1);
        }
    }

    NFSM(set<int>& accepting_states, vector<map<char, set<int> > >& edges) {
        this->accepting_states = accepting_states;
        this->edges = edges;
        start = 0;
    }

    bool accepts(string& word) {
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
private:
    set<int> accepting_states;
    vector<map<char, set<int> > > edges;
    int start;
};

int main() {
    freopen("problem2.in", "r", stdin);
    freopen("problem2.out", "w", stdout);

    string word;
    cin >> word;

    NFSM fsm;
    if (fsm.accepts(word))
        cout << "Accepts";
    else
        cout << "Rejects";
    return 0;
}