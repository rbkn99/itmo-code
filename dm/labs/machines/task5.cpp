//
// Created by matveich on 07.05.18.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

class Wrapper {   //just for debug in clion
public:
    void init(int n) {
        sums_prev.resize((ui)n);
        sums_curr.resize((ui)n);
        ast.resize((ui)n);
    }

    vector<bool> ast;   // true if terminated state is accepted
    vector<map<int, int> > edges;
    vector<map<char, set<int> > > nfa_edges;
    vector<ll> sums_prev, sums_curr;
    set<int> accepting_states, prev, curr, nfa_as;

    const int MOD = 1000000000 + 7;

    ll get_answ(int l) {
        bfs(l);
        ll answer = 0;
        for (auto as: accepting_states) {
            answer = (answer + sums_prev[as]) % MOD;
        }
        return answer % MOD;
    }

    void bfs(int l) {
        prev.insert(0);
        sums_prev[0] = 1;
        for (int i = 0; i < l; i++) {
            if (prev.empty())
                return;
            for (auto p: prev) {
                for (auto edge: edges[p]) {
                    curr.insert(edge.first);
                    sums_curr[edge.first] = (sums_curr[edge.first] + (sums_prev[p] * edge.second) % MOD) % MOD;
                }
            }
            prev = curr;
            sums_prev = sums_curr;
            curr.clear();
            fill(sums_curr.begin(), sums_curr.end(), 0);
        }
    }

    void buildDFAbyNFA() {
        map<set<int>, int> used;
        queue<set<int> > q;
        set<int> start;
        start.insert(0);
        q.push(start);
        used[start] = 0;
        int c = 0;
        edges.emplace_back(map<int, int>());
        if (nfa_as.find(0) != nfa_as.end())
            accepting_states.insert(0);
        while (!q.empty()) {
            auto s = q.front();
            q.pop();
            set<int> new_s;
            bool is_terminal;
            for (int i = 0; i < 26; i++) {
                new_s.clear();
                is_terminal = false;
                for (auto el: s) {
                    for (auto x: nfa_edges[el][i + 'a']) {
                        new_s.insert(x);
                        is_terminal |= nfa_as.find(x) != nfa_as.end();
                    }
                }
                if (new_s.empty())
                    continue;
                if (used.count(new_s) == 0) {
                    used[new_s] = ++c;
                    if (is_terminal)
                        accepting_states.insert(c);
                    q.push(new_s);
                    edges.emplace_back(map<int, int>());
                }
                edges[used[s]][used[new_s]]++;
            }
        }
        init((int)edges.size());
    }
};

int main() {
    freopen("problem5.in", "r", stdin);
    freopen("problem5.out", "w", stdout);

    int n, m = 0, k = 0, l = 0, x;
    cin >> n >> m >> k >> l;
    Wrapper wrapper;
    wrapper.nfa_edges.resize((ui)n);
    for (int i = 0; i < k; i++) {
        cin >> x;
        wrapper.nfa_as.insert(x - 1);
    }
    int a = 0, b = 0;
    char c = ' ';

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        wrapper.nfa_edges[a  - 1][c].insert(b - 1);
    }
    wrapper.buildDFAbyNFA();
    cout << wrapper.get_answ(l);
    return 0;
}
