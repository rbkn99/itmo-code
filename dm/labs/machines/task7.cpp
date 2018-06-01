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
        as1.resize((ui)n);
    }

    void init2(int n) {
        edges2.resize((ui)n);
        as2.resize((ui)n);
    }

    vector<map< char, int> > edges1, edges2;
    vector<bool> as1, as2;
    bool used[1001][1001];

    void add_devil(vector<map<char, int> >& edges) {
        edges.emplace_back(map<char, int>());
        auto n = (int)edges.size();
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < 26; c++) {
                if (edges[i].count(char(c + 'a')) == 0) {
                    edges[i][char(c + 'a')] = n - 1;
                }
            }
        }
    }

    bool bfs() {
        add_devil(edges1);
        add_devil(edges2);
        as1.emplace_back(false);
        as2.emplace_back(false);

        queue<pair<int, int> > q;
        q.push(make_pair(0, 0));
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            if (as1[p.first] != as2[p.second])
                return false;
            used[p.first][p.second] = true;
            for (int i = 0; i < 26; i++) {
                auto a = edges1[p.first][char(i + 'a')],
                b = edges2[p.second][char(i + 'a')];
                if (!used[a][b])
                    q.push(make_pair(a, b));
            }
        }
        return true;
    }
};

int main() {
    freopen("equivalence.in", "r", stdin);
    freopen("equivalence.out", "w", stdout);

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
        wrapper.edges1[a - 1][c] = b - 1;
    }
    cin >> n >> m >> k;
    wrapper.init2(n);
    for (int i = 0; i < k; i++) {
        cin >> x;
        wrapper.as2[x - 1] = true;
    }
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        wrapper.edges2[a - 1][c] = b - 1;
    }
    cout << (wrapper.bfs() ? "YES" : "NO");
    return 0;
}