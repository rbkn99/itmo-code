//
// Created by matveich on 29.05.18.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

typedef unsigned int ui;

unordered_map<char, std::vector<std::string>> cfg;

bool accepts(char c, std::string &word, int j) {
    if (j == word.size())
        return false;
    bool result = false;
    for (auto &it: cfg[c]) {
        if (it.size() == 1)
            result |= (it[0] == word.back() && j == word.size() - 1);
        else {
            if (it[0] == word[j])
                result |= accepts(it[1], word, j + 1);
        }
    }
    return result;
}


int main() {
    freopen("automaton.in", "r", stdin);
    freopen("automaton.out", "w", stdout);
    ios::sync_with_stdio(false);
    char start = ' ';
    ui n;
    cin >> n >> start;
    char s1;
    string s2, s3;

    for (int i = 0; i < n; i++) {
        cin >> s1 >> s2 >> s3;
        cfg[s1].push_back(s3);
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> s2;
        cout << (accepts(start, s2, 0) ? "yes\n": "no\n");
    }
    return 0;
}
