//
// Created by matveich on 27.05.18.
//

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int ui;

int _time = 0, result;
vector<vector<int> > dp;
vector<vector<pair<int, int> > > tree;
vector<int> tin, tout, weights;
vector<bool> marked, used;

void dfs(int k, int p) {
    used[k] = true;
    tin[k] = _time++;
    dp[k][0] = p;
    for (int i = 1; i < dp[k].size(); i++) {
        dp[k][i] = dp[dp[k][i - 1]][i - 1];
    }
    for (int i = 0; i < tree[k].size(); i++) {
        if (!used[tree[k][i].second])
            dfs(tree[k][i].second, k);
    }
    tout[k] = _time++;

}

bool is_parent(int v, int u) {
    return (tin[v] <= tin[u] && tout[u] <= tout[v]);
}

int lca(int v, int u) {
    if (is_parent(v, u))
        return v;
    if (is_parent(u, v))
        return u;
    for (int i = (int)dp[v].size() - 1; i >= 0; i--) {
        if (!is_parent(dp[v][i], u))
            v = dp[v][i];
    }
    return dp[v][0];
}

int find(int v) {
    used[v] = true;
    int sum = 0;

    for (int i = 0; i < tree[v].size(); i++) {
        int to = tree[v][i].second;
        if (!used[to]) {
            int j = tree[v][i].first;
            int tmp = find(to);
            if (tmp < 0 && marked[j]) {
                marked[j] = false;
                result--;
            }
            sum += tmp;
        }
    }
    return v == 0 ? result : sum + weights[v];
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    tin.resize((ui)n);
    tout.resize((ui)n);
    marked.resize((ui)n, true);
    weights.resize((ui)n);
    dp.resize((ui)n);
    tree.resize((ui)n);
    used.resize((ui)n);

    for (int i = 0; i < n; i++)
        dp[i].resize(17);   // log 100000

    int x, y = 0;
    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y;
        x--;
        y--;
        tree[x].push_back(make_pair(i, y));
        tree[y].push_back(make_pair(i, x));
    }
    dfs(0, 0);

    int m;
    cin >> m;
    result = n - 1;

    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        x--;
        y--;
        weights[x]--;
        weights[y]--;
        weights[lca(x, y)] += 2;
    }
    used.assign((ui)n, false);
    cout << find(0) << endl;
    return 0;
}