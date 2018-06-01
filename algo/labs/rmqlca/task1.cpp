//
// Created by matveich on 12.05.18.
//

#include <iostream>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

ui a, b;
ui cur = 0;
ui nextRand() {
    cur = cur * a + b;
    return cur >> 8;
}

const int n = 1 << 24;

ui arr[n + 1], prefix[n + 1];

int main() {
    freopen("fastadd.in", "r", stdin);
    freopen("fastadd.out", "w", stdout);

    int m, q = 0;
    cin >> m >> q >> a >> b;
    for (int i = 0; i <= n; i++)
        arr[i] = 0;
    ui add, l, r;
    for (int i = 0; i < m; i++) {
        add = nextRand();
        l = nextRand();
        r = nextRand();
        if (l > r) swap(l, r);
        arr[l] += add;
        arr[r + 1] -= add;
    }
    ui s = 0;
    for (int i = 0; i < n; i++) {
        s += arr[i];
        arr[i] = s;
    }
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++)
        prefix[i] = prefix[i - 1] + arr[i];
    s = 0;
    for (int i = 0; i < q; i++) {
        l = nextRand();
        r = nextRand();
        if (l > r) swap(l, r);
        if (l == 0)
            s += prefix[r];
        else
            s += prefix[r] - prefix[l - 1];
    }
    cout << s;
    return 0;
}