//
// Created by matveich on 07.05.18.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

typedef unsigned int ui;
typedef unsigned long ul;

class Wrapper {   //just for debug in clion
public:
    void init1(int n) {
        edges1.resize((ui)n);
        used1.resize((ui)n);
        as1.resize((ui)n);
    }

    void init2(int n) {
        edges2.resize((ui)n);
        used2.resize((ui)n);
        as2.resize((ui)n);
    }

    vector<vector<pair< char, int> > > edges1, edges2;
    vector<bool> used1, used2, as1, as2;

    void sort_edges() {
        for (int i = 0; i < edges1.size(); i++)
            sort(edges1[i].begin(), edges1[i].end());
        for (int i = 0; i < edges2.size(); i++)
            sort(edges2[i].begin(), edges2[i].end());
    }

    bool dfs(int x, int y) {
        used1[x] = used2[y] = true;
        if (as1[x] != as2[y])
            return false;
        bool result = true;
        vector<char> v1, v2;
        for (auto a: edges1[x])
            v1.push_back(a.first);
        for (auto a: edges2[y])
            v2.push_back(a.first);
        if (v1 != v2)
            return false;
        for (int i = 0; i < edges1[x].size(); i++) {
            auto x1 = edges1[x][i].second, y1 = edges2[y][i].second;
            if (used1[x1] != used2[y1])
                return false;
            if (!used1[x1])
                result &= dfs(x1, y1);
        }
        return result;
    }
};

int main() {
    freopen("isomorphism.in", "r", stdin);
    freopen("isomorphism.out", "w", stdout);

    int n, m = 0, k = 0, x;
    cin >> n >> m >> k;
    Wrapper wrapper;
    int a = 0, b = 0;
    char c = ' ';
    wrapper.init1(n);
    for (int i = 0; i < k; i++) {
        cin >> x;
        wrapper.as1[x - 1] = true;
    }
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        wrapper.edges1[a - 1].push_back(make_pair(c, b - 1));
    }
    cin >> n >> m >> k;
    wrapper.init2(n);
    for (int i = 0; i < k; i++) {
        cin >> x;
        wrapper.as2[x - 1] = true;
    }
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        wrapper.edges2[a - 1].push_back(make_pair(c, b - 1));
    }
    wrapper.sort_edges();
    cout << (wrapper.dfs(0, 0) ? "YES" : "NO");
    return 0;
}