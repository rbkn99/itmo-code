//
// Created by matveich on 17.05.18.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef unsigned int ui;
typedef long long ll;


struct Query {
    int l, r, id;
};

vector<int> arr;
vector<ll> cnt;
vector<Query> requests;
int k;

ll result = 0;

bool cmp(const Query& x, const Query& y) {
    if (x.l / k != y.l / k)
        return x.l < y.l;
    return x.r < y.r;
}

void add(int i) {
    ll value = arr[i];
    if (cnt[value] > 0)
        result -= cnt[value] * cnt[value] * value;
    cnt[value] += 1;
    result += cnt[value] * cnt[value] * value;
}

void del(int i) {
    ll value = arr[i];
    result -= cnt[value] * cnt[value] * value;
    cnt[value]--;
    if (cnt[value] > 0)
        result += cnt[value] * cnt[value] * value;
}

int main() {
    freopen("fun.in", "r", stdin);
    freopen("fun.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    int n, m = 0;
    cin >> n >> m;
    arr.resize((ui)n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    requests.resize((ui)m);
    cnt.resize(1000001);
    for (int i = 0; i < m; i++) {
        cin >> requests[i].l >> requests[i].r;
        requests[i].l--;
        requests[i].r--;
        requests[i].id = i;
    }
    k = int(sqrt(n));
    int a = 1, b = 0;
    sort(requests.begin(), requests.end(), cmp);
    vector<ll> answers((ui)m);
    for (int i = 0; i < m; i++) {
        while (a > requests[i].l) {
            add(a - 1);
            a--;
        }
        while (b < requests[i].r) {
            add(b + 1);
            b++;
        }
        while (a < requests[i].l) {
            del(a);
            a++;
        }
        while (b > requests[i].r) {
            del(b);
            b--;
        }
        answers[requests[i].id] = result;
    }
    for (int i = 0; i < m; i++) {
        cout << answers[i] << endl;
    }
    return 0;
}