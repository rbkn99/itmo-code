//
// Created by matveich on 27.05.18.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

class SegmentTree {
public:
    explicit SegmentTree(vector<ll>& a) {
        n = (ui)a.size();
        ui p = 1;
        while (p < n)
            p <<= 1;
        n = p;
        a.resize((ui)n, MAX);
        tree.resize((ui)2 * n, vector<ll>());
        for (ui i = 0; i < a.size(); i++)
            tree[n + i] = vector<ll>({a[i]});
        for (ui i = n - 1; i > 0; i--)
            tree[i] = merge_nodes(tree[2 * i], tree[2 * i + 1]);
    }

    ui request(ui l, ui r, ui x, ui y) {
        l += n;
        r += n;
        ui l_res = 0;
        ui r_res = 0;
        while (l < r) {
            if (l % 2 == 1) {
                l_res += f(tree[l], x, y);
                l++;
            }
            l /= 2;
            if (r % 2 == 0) {
                r_res += f(tree[r], x, y);
                r--;
            }
            r /= 2;
        }
        if (l == r)
            l_res += f(tree[l], x, y);
        return l_res + r_res;
    }
private:
    const ll MAX = INT64_MAX;
    ui n;
    vector<vector<ll> > tree;

    ui f(vector<ll>& v, ll l, ll r) {
        return static_cast<ui>(upper_bound(v.begin(), v.end(), r) - lower_bound(v.begin(), v.end(), l));
    }

    vector<ll> merge_nodes(vector<ll>& a, vector<ll>& b) {
        size_t it1 = 0, it2 = 0;
        vector<ll> result;
        for (; it1 < a.size() && it2 < b.size();) {
            if (a[it1] < b[it2])
                result.push_back(a[it1++]);
            else
                result.push_back(b[it2++]);
        }
        while (it1 < a.size())
            result.push_back(a[it1++]);
        while (it2 < b.size())
            result.push_back(b[it2++]);
        return result;
    }
};

unsigned int a, b;
unsigned int cur = 0;
unsigned int nextRand17() {
    cur = cur * a + b;
    return (cur >> (ui)15);
}

unsigned int nextRand24() {
    cur = cur * a + b;
    return (cur >> (ui)8);
}

int main() {
    freopen("find2d.in", "r", stdin);
    freopen("find2d.out", "w", stdout);
    int q;
    cin >> q >> a >> b;
    ui n = (1 << 17);
    vector<ll> f(n);
    for (int i = 0; i < n; i++)
        f[i] = nextRand24();
    SegmentTree st(f);
    ui answer = 0;
    for (int i = 0; i < q; i++) {
        ui l = nextRand17(), r = nextRand17();
        if (l > r) swap(l, r);
        ui x = nextRand24(), y = nextRand24();
        if (x > y) swap(x, y);
        auto tmp = st.request(l, r, x, y);
        answer += tmp;
        b += tmp;
    }
    cout << answer;
    return 0;
}