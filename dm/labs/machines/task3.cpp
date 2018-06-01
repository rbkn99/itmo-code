//
// Created by matveich on 07.05.18.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

class Wrapper {   //just for debug in clion
public:
    explicit Wrapper(int n) {
        edges.resize((ui)n);
        reversed_edges.resize((ui)n);
        sums.resize((ui)n);
        ast.resize((ui)n);
        used.resize((ui)n);
        tin.resize((ui)n, -1);
        for (int i = 0; i < n; i++) {
            tout.emplace_back(make_pair(-1, i));
        }
    }
    vector<int> tin;
    vector<pair<int, int> > tout;
    vector<bool> ast;   // true if terminated state is accepted
    vector<map<int, int> > edges, reversed_edges;
    vector<ll> sums;
    set<int> accepting_states;
    vector<int> used;

    const int MOD = 1000000000 + 7;

    void dfs1(int k) {
        ast[k] = true;
        for (auto edge: reversed_edges[k]) {
            if (!ast[edge.first]) {
                dfs1(edge.first);
            }
        }
    }
    void fill() {
        for (auto state: accepting_states) {
            if (!used[state]) {
                dfs1(state);
            }
        }
    }
    int t = 0;
    bool infinity = false;

    void top_sort(int k) {
        tin[k] = t++;
        ll sum = 0;
        for (auto edge: edges[k]) {
            if (!ast[edge.first])
                continue;
            if (tin[edge.first] == -1) {
                top_sort(edge.first);
                if (infinity)
                    return;
            }
            else if (tout[edge.first].first == -1) {
                infinity = true;
            }
        }
        tout[k].first = t++;
    }

    void summarize() {
        sums[0] = 1;
        for (int i = (int)tout.size() - 1; i >= 0; i--) {
            if (!ast[tout[i].second])
                continue;
            do_it(tout[i].second);
        }
    }

    void do_it(int k) {
        for (auto edge: edges[k]) {
            if (!ast[edge.first])
                continue;
            sums[edge.first] = (sums[edge.first] + edge.second * sums[k]) % MOD;
        }
    }

    ll answer() {
        ll sum = 0;
        for (auto state: accepting_states) {
            sum = (sum + sums[state]) % MOD;
        }
        return sum;
    }
};

int main() {
    freopen("problem3.in", "r", stdin);
    freopen("problem3.out", "w", stdout);

    int n, m = 0, k = 0, x;
    cin >> n >> m >> k;
    Wrapper wrapper(n);
    for (int i = 0; i < k; i++) {
        cin >> x;
        wrapper.accepting_states.insert(x - 1);
    }
    int a = 0, b = 0;
    char c = ' ';

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        wrapper.edges[a - 1][b - 1]++;
        wrapper.reversed_edges[b - 1][a - 1]++;
    }
    wrapper.fill();
    wrapper.top_sort(0);
    if (wrapper.infinity) {
        cout << -1;
        return 0;
    }
    sort(wrapper.tout.begin(), wrapper.tout.end());
    wrapper.summarize();
    cout << wrapper.answer();
    return 0;
}
