//
// Created by matveich on 12.05.18.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

int n, m, a1, u1, v1;
vector<vector<int> > st;
vector<int> a;
int logn;


int req(int l, int r) {
    if (l > r)
        swap(l, r);
    auto j = (int)log2(r - l + 1);
    return min(st[l][j], st[r - (1 << j) + 1][j]);
}

int main() {
    freopen("sparse.in", "r", stdin);
    freopen("sparse.out", "w", stdout);
    cin >> n >> m >> a1 >> u1 >> v1;
    int maxn = 16714589;
    logn = (int)log2(n) + 1;
    st.resize((ui)n + 1);
    a.resize((ui)n + 1);
    a[1] = a1;
    for (int i = 2; i <= n; i++)
        a[i] = (23 * a[i - 1] + 21563) % maxn;
    for (int i = n; i > 0; i--) {
        st[i].resize((ui)logn, maxn + 1);
        st[i][0] = a[i];
        for (int j = 1; j < logn; j++) {
            int q = i + (1 << (j - 1));
            st[i][j] = st[i][j - 1];
            if (q <= n)
                st[i][j] = min(st[i][j], st[q][j - 1]);
        }
    }

    int answ = req(u1, v1);
    int u2 = u1, v2 = v1;
    for (int i = 1; i < m; i++) {
        u1 = ((17 * u2 + 751 + answ + 2 * i) % n) + 1;
        v1 = ((13 * v2 + 593 + answ + 5 * i) % n) + 1;
        u2 = u1;
        v2 = v1;
        answ = req(u1, v1);
    }
    cout << u1 << " " << v1 << " " << answ;
    return 0;
}