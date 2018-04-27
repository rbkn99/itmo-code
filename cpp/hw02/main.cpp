#include <iostream>
#include <limits>
#include "big_integer.h"

int main() {
    //big_integer a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    //big_integer b(                                                     "100000000000000000000000000000000000000");
    //big_integer c("100000000000000000000000000000000000000000000000000000");
    big_integer a = 5, b = 4;
    big_integer c = a + b;
    cout << to_string(a + b) << endl;
    //cout << static_cast<ui>(std::numeric_limits<int>::min()) << endl;
    return 0;
}