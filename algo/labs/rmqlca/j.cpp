//
// Created by matveich on 12.05.18.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

struct Vertex {
    int x, delta;
    bool prop_mode;

    explicit Vertex() {}
    explicit Vertex(int x): x(x), prop_mode(false), delta(0) {}

    int get_val() {
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
            tree[i] = Vertex(f(tree[2 * i].x, tree[2 * i + 1].x));
    }

    int request(int l, int r) {
        return request(1, 0, n, l, r);
    }

    void upd(int l, int r, int val, bool delta_mode) {
        if (l > r)
            swap(l, r);
        upd(1, 0, n, l, r, val, delta_mode);
    }

    int max_ind() {
        int i = 1;
        push(i);
        int max_val = tree[i].get_val();
        while (2 * i < tree.size()) {
            push(i);
            if (tree[2 * i].get_val() == max_val)
                i *= 2;
            else
                i = i * 2 + 1;
        }
        return i - n;
    }

private:
    const Vertex Z = Vertex(0);
    int n;
    vector<Vertex> tree;

    int f(int a, int b) {
        return max(a, b);
    }

    int request(int i, int tl, int tr, int l, int r) {
        if (r <= tl || tr <= l)
            return Z.x;
        if (l <= tl && tr <= r)
            return tree[i].get_val();
        push(i);
        auto tm = (tl + tr) / 2;
        int res1 = request(i * 2, tl, tm, l, r);
        int res2 = request(i * 2 + 1, tm, tr, l, r);
        return f(res1, res2);
    }

    void upd(int i, int tl, int tr, int l, int r, int x, bool delta_mode=true) {
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
        tree[i].x = f(tree[i * 2].get_val(), tree[i * 2 + 1].get_val());
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

struct Point {
    int x, y1, y2;
    bool mode; // 0 - in, 1 - out
};

const int GAP = (int)1e6 + 3;

bool cmp(const Point& p1, const Point& p2) {
    if (p1.x == p2.x)
        return p1.mode < p2.mode;
    return p1.x < p2.x;
}

int main() {
    freopen("windows.in", "r", stdin);
    freopen("windows.out", "w", stdout);
    int n;
    cin >> n;
    vector<Point> vp;
    int x1, x2 = 0, y1 = 0, y2 = 0;
    for (int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += GAP;
        x2 += GAP;
        y1 += GAP;
        y2 += GAP;
        vp.push_back({x1, y1, y2, false});
        vp.push_back({x2, y1, y2, true});
    }
    vector<Vertex> stv((ui)GAP * 2, Vertex(0));
    SegmentTree st(stv);
    sort(vp.begin(), vp.end(), cmp);
    int _max = 0;
    int x, y;
    for (size_t i = 0; i < vp.size(); i++) {
        int yy1 = vp[i].y1;
        int yy2 = vp[i].y2;
        if (yy1 > yy2)
            swap(yy1, yy2);
        if (!vp[i].mode) {
            st.upd(yy1, yy2 + 1, 1, true);
            int tmp = st.request(0, (ui)GAP * 2);
            if (tmp > _max) {
                _max = tmp;
                x = vp[i].x;
                int max_ind = st.max_ind();
                y = max_ind;
            }
        }
        else
            st.upd(yy1, yy2 + 1, -1, true);
    }
    cout << _max << endl << x - GAP << " " << y - GAP;
    return 0;
}