//
// Created by matveich on 12.05.18.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

ll rr = 0;

struct Matrix2x2 {
    Matrix2x2(ll a, ll b, ll c, ll d) : a(a % rr), b(b % rr), c(c % rr), d(d % rr) {}
    ll a, b, c, d;
};

class SegmentTree {
public:
    explicit SegmentTree(vector<Matrix2x2>& a) {
        n = (int)a.size();
        int p = 1;
        while (p < n)
            p <<= 1;
        n = p;
        a.resize((ui)n, Z);
        tree.resize((ui)2 * n, Z);
        for (int i = 0; i < (int)a.size(); i++)
            tree[n + i] = a[i];
        for (int i = n - 1; i > 0; i--)
            tree[i] = f(tree[2 * i], tree[2 * i + 1]);
    }

    Matrix2x2 request(int l, int r) {
        l += n;
        r += n;
        Matrix2x2 l_res = Z;
        Matrix2x2 r_res = Z;
        while (l < r) {
            if (l % 2 == 1) {
                l_res = f(l_res, tree[l]);
                l++;
            }
            l /= 2;
            if (r % 2 == 0) {
                r_res = f(tree[r], r_res);
                r--;
            }
            r /= 2;
        }
        if (l == r)
            l_res = f(l_res, tree[l]);
        return f(l_res, r_res);
    }
private:
    const Matrix2x2 Z = {1, 0, 0, 1};
    int n;
    vector<Matrix2x2> tree;

    Matrix2x2 f(Matrix2x2& x, Matrix2x2& y) {
        return {
                (x.a * y.a + x.b * y.c) % rr,
                (x.a * y.b + x.b * y.d) % rr,
                (x.c * y.a + x.d * y.c) % rr,
                (x.c * y.b + x.d * y.d) % rr
        };
    }
};

int main() {
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> rr >> n >> m;
    ll a, b, c, d;
    vector<Matrix2x2> v;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> c >> d;
        v.emplace_back(Matrix2x2(a, b, c, d));
    }
    SegmentTree st(v);
    int l, r;
    for (int i = 0; i < m; i++) {
        cin >> l >> r;
        if (l > r)
            swap(l, r);
        auto tmp = st.request(l - 1, r - 1);
        cout << tmp.a << " " << tmp.b << "\n" << tmp.c << " " << tmp.d << "\n\n";
    }
    return 0;
}