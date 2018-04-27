//
// Created by matveich on 31.03.18.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Vertex {
    int x, c;  //x - number, c - number of vertexes in the subtree

    explicit Vertex(int _x) : x(_x), c(0) {}
    Vertex(int _x, int _c) : x(_x), c(_c) {}
};
vector<vector<Vertex> > g;
vector<bool> used;
int n;

int countV(int v, int prev) {
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        auto t = g[v][i];
        if (!used[t.x] && t.x != prev) {
            g[v][i].c = countV(t.x, v);
        }
    }
    int result = 0;
    for (int i = 0; i < g[v].size(); i++) {
        if (g[v][i].x != prev)
            result += g[v][i].c;
    }
    for (int i = 0; i < g[v].size(); i++) {
        if (g[v][i].x == prev) {
            g[v][i].c = n - result - 1;
            break;
        }
    }
    return result + 1;
}

void print_tree() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < g[i].size(); j++) {
            printf("%d -> %d: %d\n", i + 1, g[i][j].x + 1, g[i][j].c);
        }
    }
}

int root = -1;
bool ans = false;

unsigned long long _hash(int v) {
    used[v] = true;
    unsigned long long h = 1;
    vector<unsigned long long> h_v;
    for (int i = 0; i < g[v].size(); i++) {
        if (!used[g[v][i].x]) {
            h_v.push_back(_hash(g[v][i].x));
            h *= 31;
            h += h_v.back();
        }
    }
    if (v == root) {
        ans = (h_v[0] == h_v[1]);
    }
    return h;
}

int main() {
    cin >> n;
    g.resize((unsigned long)n);
    used.resize((unsigned long)n);
    int u, v;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        g[u - 1].push_back(Vertex(v - 1));
        g[v - 1].push_back(Vertex(u - 1));
    }
    countV(0, -1);
    //print_tree();
    for (int i = 0; i < n; i++) {
        if (g[i].size() == 2 && g[i][0].c == g[i][1].c) {
            root = i;
            break;
        }
    }
    // cout << "root -> " << root + 1 << endl;
    if (root == -1) {
        cout << "NO";
        return 0;
    }
    used.assign((unsigned long)n, false);
    _hash(root);

    if (ans) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
    return 0;
}