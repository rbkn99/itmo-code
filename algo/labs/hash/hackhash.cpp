//
// Created by matveich on 31.03.18.
//

#include <iostream>
using namespace std;

int main() {
    int k;
    string s;
    for (int i = 0; i < 1000; i++)
        s.push_back('B');
    cin >> k;
    for (int i = 0; i < 998 && k > 0; i++, k--) {
        s[i] = char(s[i] - 1);
        s[i + 1] = char(s[i + 1] + 31);
        cout << s << endl;
        s[i] = char(s[i] + 1);
        s[i + 1] = char(s[i + 1] - 31);
    }
    for (int i = 0; i < 996 && k > 0; i++, k--) {
        s[i] = char(s[i] - 1);
        s[i + 1] = char(s[i + 1] + 31);
        s[i + 2] = char(s[i + 2] - 1);
        s[i + 3] = char(s[i + 3] + 31);
        cout << s << endl;
        s[i] = char(s[i] + 1);
        s[i + 1] = char(s[i + 1] - 31);
        s[i + 2] = char(s[i + 2] + 1);
        s[i + 3] = char(s[i + 3] - 31);
    }
    return 0;
}