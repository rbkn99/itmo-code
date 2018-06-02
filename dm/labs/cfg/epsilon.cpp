//
// Created by matveich on 02.06.18.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <iterator>
#include <sstream>
#include <queue>

using namespace std;

typedef unsigned int ui;

vector<string> split_by_spaces(string& s) {
    istringstream iss(s);
    vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());
    return results;
}

int main() {
    freopen("epsilon.in", "r", stdin);
    freopen("epsilon.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    int n;
    char start = ' ';
    cin >> n >> start;

    queue<char> q;

    string s;
    getline(cin, s);

    vector<pair<char, int> > s_right((ui)n);
    vector<bool> is_eps(26), marked(26);
    vector<vector<int> > cfg(26);

    for (int i = 0; i < n; i++) {
        char c;
        string right;

        getline(cin, s);
        auto ss = split_by_spaces(s);
        c = ss[0][0] - 'A';

        if (ss.size() == 2) {
            q.push(c);
            is_eps[c] = true;
            continue;
        }

        s_right[i].first = c;
        for (int j = 0; j < ss[2].size(); j++) {
            s_right[i].second++;
            if ('A' <= ss[2][j] && ss[2][j] <= 'Z')
                cfg[ss[2][j] - 'A'].push_back(i);
        }
    }

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        if (marked[v])
            continue;
        marked[v] = true;
        for (auto &to: cfg[v]) {
            s_right[to].second--;
            if (s_right[to].second == 0) {
                q.push(s_right[to].first);
                is_eps[s_right[to].first] = true;
            }
        }
    }
    for (int i = 0; i < is_eps.size(); i++) {
        if (is_eps[i])
            cout << char('A' + i) << endl;
    }
    return 0;
}