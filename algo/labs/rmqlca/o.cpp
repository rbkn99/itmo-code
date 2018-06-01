//
// Created by matveich on 12.05.18.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

const int MAX = 10000000;

int n;
vector<int> weights, p, depths, logs;
vector<vector<int> > min_edges;
vector<vector<int> > dp;


int lca(int l, int r) {
    int answer = MAX;
    int diff = 0;
    while (depths[l] < depths[r]) {
        diff = depths[r] - depths[l];
        answer = min(answer, min_edges[logs[diff]][r]);
        r = dp[logs[diff]][r];
    }
    while (depths[l] > depths[r]) {
        diff = depths[l] - depths[r];
        answer = min(answer, min_edges[logs[diff]][l]);
        l = dp[logs[diff]][l];
    }
    int k = logs[depths[l]];
    while (l != r) {
        while (dp[k][l] == dp[k][r] && k > 0) k--;
        answer = min(min(answer, min_edges[k][l]), min_edges[k][r]);
        l = dp[k][l];
        r = dp[k][r];
    }
    return answer;
}

class SegmentTree {
public:
    explicit SegmentTree(vector<int>& a) {
        n = (int)a.size();
        int p = 1;
        while (p < n)
            p <<= 1;
        n = p;
        a.resize((ui)n, MAX);
        tree.resize((ui)2 * n, MAX);
        for (int i = 0; i < (int)a.size(); i++)
            tree[n + i] = a[i];
        for (int i = n - 1; i > 0; i--)
            tree[i] = f(tree[2 * i], tree[2 * i + 1]);
    }

    int request(int l, int r) {
        l += n;
        r += n;
        int l_res = MAX;
        int r_res = MAX;
        while (l < r) {
            if (l % 2 == 1) {
                l_res = f(l_res, tree[l]);
                l++;
            }
            l /= 2;
            if (r % 2 == 0) {
                r_res = f(r_res, tree[r]);
                r--;
            }
            r /= 2;
        }
        if (l == r)
            l_res = f(l_res, tree[l]);
        return f(l_res, r_res);
    }

    void set(int i, int x) {
        i += n;
        tree[i] = x;
        i /= 2;
        while (i > 0) {
            tree[i] = f(tree[2 * i], tree[2 * i + 1]);
            i /= 2;
        }
    }
private:
    int n;
    vector<int> tree;

    int f(int a, int b) {
        return min(a, b);
    }
};

vector<SegmentTree> vst;



int main() {
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    ios_base::sync_with_stdio(false);

    cin >> n;
    logs.resize((ui)n + 1);
    logs[0] = 0;
    for (int i = 1; i <= n; i++)
        logs[i] = int(log2(i));
    p.resize((ui)n);
    weights.resize((ui)n);
    depths.resize((ui)n);
    //vector<SegmentTree> vst;
    dp.resize((ui)logs[n] + 1);
    min_edges.resize((ui)logs[n] + 1);
    for (int i = 0; i < logs[n] + 1; i++) {
        dp[i].resize((ui)n);
        min_edges[i].resize((ui)n);
    }

    int x = 0, y = 0;
    weights[0] = MAX;
    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        x--;
        p[i] = x;
        depths[i] = depths[x] + 1;
        weights[i] = y;
    }
    dp[0] = p;
    min_edges[0] = weights;
    for (int i = 1; i < logs[n] + 1; i++) {
        for (int j = 0; j < n; j++) {
            min_edges[i][j] = min(min_edges[i - 1][j], min_edges[i - 1][dp[i - 1][j]]);
            dp[i][j] = dp[i - 1][dp[i - 1][j]];
        }
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        cout << lca(x - 1, y - 1) << endl;
    }
    return 0;
}