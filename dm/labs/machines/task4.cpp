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
        sums_prev.resize((ui)n);
        sums_curr.resize((ui)n);
        ast.resize((ui)n);
    }
    vector<bool> ast;   // true if terminated state is accepted
    vector<map<int, int> > edges;
    vector<ll> sums_prev, sums_curr;
    set<int> accepting_states, prev, curr;

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
};

int main() {
    freopen("problem4.in", "r", stdin);
    freopen("problem4.out", "w", stdout);

    int n, m = 0, k = 0, l = 0, x;
    cin >> n >> m >> k >> l;
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
    }
    cout << wrapper.get_answ(l);
    return 0;
}