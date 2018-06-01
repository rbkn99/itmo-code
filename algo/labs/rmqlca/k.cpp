//
// Created by matveich on 16.05.18.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <climits>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

using namespace std;

int n, logn;
vector < vector<int> > g;
vector<int> tin, tout;
int timer = 0;
vector<vector<int> > dp;

void dfs(int k, int p=0) {
    tin[k] = ++timer;
    dp[k][0] = p;
    for (int i = 1; i < logn; i++)
        dp[k][i] = dp[dp[k][i - 1]][i - 1];
    for (int i = 0; i < g[k].size(); i++) {
        int to = g[k][i];
        if (to != p)
            dfs(to, k);
    }
    tout[k] = ++timer;
}

bool is_parent(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
    if (is_parent(v, u))
        return v;
    if (is_parent(u, v))
        return u;
    for (int i = logn - 1; i >= 0; i--)
        if (!is_parent(dp[v][i], u))
            v = dp[v][i];
    return dp[v][0];
}

int main() {
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
    ios_base::sync_with_stdio(false);

    cin >> n;
    logn = (int)log2(n) + 1;
    g.resize((ui)n);
    dp.resize((ui)n);
    for (int i = 0; i < n; i++)
        dp[i].resize((ui)logn);
    tin.resize((ui)n);
    tout.resize((ui)n);
    vector<pair<int, int> > reqs;
    string s;
    int x = 0, y = 0;
    while (!cin.eof()) {
        s = "";
        cin >> s >> x >> y;
        if (s == "ADD")
            g[x - 1].push_back(y - 1);
        else if (s == "GET")
            reqs.emplace_back(make_pair(x - 1, y - 1));
    }
    dfs(0);
    for (auto pp: reqs) {
        cout << lca(pp.first, pp.second) + 1 << endl;
    }
    return 0;
}