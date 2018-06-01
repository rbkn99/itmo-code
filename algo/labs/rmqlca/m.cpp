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
vector<vector<int> > g;
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
    freopen("lca_rmq.in", "r", stdin);
    freopen("lca_rmq.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    int m = 0;
    cin >> n >> m;
    logn = (int)log2(n) + 1;

    g.resize((ui)n);
    dp.resize((ui)n);
    for (int i = 0; i < n; i++)
        dp[i].resize((ui)logn);
    tin.resize((ui)n);
    tout.resize((ui)n);

    ll x = 0, y = 0, z = 0;
    for (int i = 1; i < n; i++) {
        cin >> x;
        g[x].push_back(i);
    }
    dfs(0);
    vector<ll> a((ui)m * 2 + 1);
    cin >> a[1] >> a[2];
    cin >> x >> y >> z;
    for (int i = 3; i <= 2 * m; i++) {
        a[i] = (x * a[i - 2] + y * a[i - 1] + z) % n;
    }

    ll xx = a[1], yy = a[2], answer = 0;
    int delta;
    for (int i = 2; i <= m + 1; i++) {
        delta = lca(xx, yy);
        answer += delta;
        if (i != m + 1) {
            xx = (a[2 * i - 1] + delta) % n;
            yy = a[2 * i];
        }
    }
    cout << answer;
    return 0;
}