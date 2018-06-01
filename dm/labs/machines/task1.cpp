//
// Created by matveich on 07.05.18.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

typedef unsigned int ui;

class FSM {
public:
    FSM() {
        start = 0;
    }

    FSM(vector<int>& accepting_states, vector<map<char, int> >& edges) {
        this->accepting_states = accepting_states;
        this->edges = edges;
        start = 0;
    }

    bool in_accepting_state(int state) {
        for (int accepting_state: accepting_states) {
            if (accepting_state == state)
                return true;
        }
        return false;
    }

    bool accepts(string& word) {
        int state = start;
        for (char c: word) {
            if (edges[state].count(c) == 0)
                return false;
            state = edges[state][c];
        }
        return in_accepting_state(state);
    }
private:
    vector<int> accepting_states;
    vector<map<char, int> > edges;
    int start;
};

int main() {
    freopen("problem1.in", "r", stdin);
    freopen("problem1.out", "w", stdout);

    string word;
    cin >> word;
    int n, m = 0, k = 0;
    cin >> n >> m >> k;
    vector<int> as((ui)k);
    int x, a = 0, b = 0;
    char c = ' ';
    for (int i = 0; i < k; i++) {
        cin >> x;
        as.push_back(x - 1);
    }
    vector<map<char, int> > edges((ui)n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        edges[a - 1][c] = b - 1;
    }
    FSM fsm(as, edges);
    if (fsm.accepts(word))
        cout << "Accepts";
    else
        cout << "Rejects";
    return 0;
}