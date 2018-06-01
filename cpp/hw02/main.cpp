#include <iostream>
#include <limits>
#include <cassert>
#include "big_integer.h"

int main() {
    big_integer a = (1 << 25);
    auto b = a.__quotient(1 << 23);
    std::cout << "hui";
    return 0;
}