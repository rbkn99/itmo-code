//
// Created by matveich on 12.05.18.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

struct Vertex {
    ll x, delta;
    bool prop_mode;

    explicit Vertex() {}
    explicit Vertex(ll x): x(x), prop_mode(false), delta(0) {}

    ll get_val() {
        return x + delta;
    }
};

class SegmentTree {
public:
    explicit SegmentTree(vector<Vertex>& a) {
        n = (int)a.size();
        int p = 1;
        while (p < n)
            p <<= 1;
        n = p;
        tree.resize((ui)2 * n);
        for (int i = 0; i < (int)a.size(); i++)
            tree[n + i] = Vertex(a[i]);
        for (int i = n - 1; i > 0; i--)
            tree[i] = Vertex(min(tree[2 * i].x, tree[2 * i + 1].x));
    }

    ll request(int l, int r) {
        return request(1, 0, n, l, r);
    }

    void upd(int l, int r, ll val, bool delta_mode) {
        upd(1, 0, n, l, r, val, delta_mode);
    }

private:
    const Vertex Z = Vertex((ll)1e18 * 2 + 1);
    int n;
    vector<Vertex> tree;

    ll request(int i, int tl, int tr, int l, int r) {
        if (r <= tl || tr <= l)
            return Z.x;
        if (l <= tl && tr <= r)
            return tree[i].get_val();
        push(i);
        auto tm = (tl + tr) / 2;
        ll res1 = request(i * 2, tl, tm, l, r);
        ll res2 = request(i * 2 + 1, tm, tr, l, r);
        return min(res1, res2);
    }

    void upd(int i, int tl, int tr, int l, int r, ll x, bool delta_mode=true) {
        if (r <= tl || tr <= l)
            return;
        if (l <= tl && tr <= r) {
            if (delta_mode) {
                tree[i].delta += x;
            }
            else {
                tree[i].delta = 0;
                tree[i].x = x;
                tree[i].prop_mode = true;
            }
            return;
        }
        push(i);
        auto tm = (tl + tr) / 2;
        upd(i * 2, tl, tm, l, r, x, delta_mode);
        upd(i * 2 + 1, tm, tr, l, r, x, delta_mode);
        tree[i].x = min(tree[i * 2].get_val(), tree[i * 2 + 1].get_val());
    }

    void push(int i) {
        tree[2 * i].delta += tree[i].delta;
        tree[2 * i + 1].delta += tree[i].delta;
        tree[i].x += tree[i].delta;
        tree[i].delta = 0;
        if (tree[i].prop_mode) {
            tree[2 * i].prop_mode = tree[2 * i + 1].prop_mode = true;
            tree[2 * i].x = tree[2 * i + 1].x = tree[i].x;
            tree[2 * i].delta = tree[2 * i + 1].delta = 0;
            tree[i].prop_mode = false;
        }
    }
};

int main() {
    freopen("rmq2.in", "r", stdin);
    freopen("rmq2.out", "w", stdout);
    int n;
    cin >> n;
    ll t = 0;
    vector<Vertex> a;
    for (int i = 0; i < n; i++) {
        cin >> t;
        a.emplace_back(Vertex(t));
    }
    SegmentTree st(a);
    string req;
    int x, y = 0;
    while (!cin.eof()) {
        req = "";
        cin >> req;
        if (req == "min") {
            cin >> x >> y;
            cout << st.request(x - 1, y) << endl;
            continue;
        }
        cin >> x >> y >> t;
        st.upd(x - 1, y, t, req == "add");
    }
    return 0;
}