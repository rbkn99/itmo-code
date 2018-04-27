#include <iostream>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

int main() {
    ifstream out1("linkedmap.out"), out2("answers_linkedmap.out");
    ifstream in("linkedmap.in");
    string out_coms[] = {"get", "prev", "next"};
    string s1, s2, s = "", in_key;
    int c = 1;
    int cc = 0;
    while (!out1.eof()) {
        out1 >> s1;
        out2 >> s2;
        in >> s >> in_key;
        cc++;
        if (s == "put")
            in >> in_key;
        while (!in.eof() && out_coms[0] != s && out_coms[1] != s && out_coms[2] != s) {
            in >> s >> in_key;
            cc++;
            if (s == "put")
                in >> in_key;
        }
        if (s1 != s2) {
            cout << "huinya happened at " << c << " line\n";
            cout << "request: " << s << " " << in_key << " at line " << cc << endl;
            cout << "expected:\n" << s2 << endl;
            cout << "actual:\n" << s1 << endl;
            cout << "--------------------------\n\n";
        }
        c++;
    }
    return 0;
}