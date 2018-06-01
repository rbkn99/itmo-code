//
// Created by matveich on 12.05.18.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

class SegmentTree {
public:
    explicit SegmentTree(vector<ll>& a) {
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

    ll request(int l, int r) {
        l += n;
        r += n;
        ll l_res = MAX;
        ll r_res = MAX;
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

    void set(int i, ll x) {
        i += n;
        tree[i] = x;
        i /= 2;
        while (i > 0) {
            tree[i] = f(tree[2 * i], tree[2 * i + 1]);
            i /= 2;
        }
    }
private:
    const ll MAX = 0;
    int n;
    vector<ll> tree;

    ll f(ll a, ll b) {
        return a + b;
    }
};

int main() {
    freopen("rsq.in", "r", stdin);
    freopen("rsq.out", "w", stdout);
    int n;
    cin >> n;
    vector<ll> a((ui)n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    SegmentTree st(a);
    string req;
    ll x = 0, y = 0;
    while (!cin.eof()) {
        req = "";
        cin >> req >> x >> y;
        if (req == "sum")
            cout << st.request((int)x - 1, (int)y - 1) << endl;
        else if (req == "set")
            st.set((int)x - 1, y);
        else
            continue;
    }
    return 0;
}