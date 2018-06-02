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


using namespace std;

typedef unsigned int ui;

unordered_map<char, vector<string> > cfg;
unordered_map<char, bool> eps;

bool product_eps(char c) {
    if (eps[c])
        return true;
    bool result = false;
    for (auto &it: cfg[c]) {
        bool flag = true;
        for (auto& cr: it) {
            if ('a' <= cr && cr <= 'z') {
                flag = false;
                break;
            }
        }
        if (!flag)
            continue;
        result = true;
        for (auto& cr: it) {
            result &= product_eps(cr);
            if (result)
                break;
        }
        if (result)
            break;
    }
    eps[c] = result;
    return result;
}

vector<string> split_by_spaces(string& s) {
    istringstream iss(s);
    vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());
    return results;
}

int main() {
    freopen("epsilon.in", "r", stdin);
    freopen("epsilon.out", "w", stdout);
    ios::sync_with_stdio(false);
    char start = ' ';
    ui n;
    cin >> n >> start;
    string s = " ";

    while(!cin.eof()) {
        getline(cin, s);
        if (s.empty())
            continue;
        auto ss = split_by_spaces(s);
        if (ss.size() == 2) {
            eps[ss[0][0]] = true;
            cfg[ss[0][0]].clear();
        }
        else
            cfg[ss[0][0]].push_back(ss[2]);
    }
    for (auto &it: cfg) {
        if (product_eps(it.first))
            cout << it.first << endl;
    }
    return 0;
}
