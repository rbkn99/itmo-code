#include <iostream>

#include "vector.h"
#include <cassert>

typedef vector<int> vi;
std::string base_str = "7 7 7 ";

//test constructors
void test1() {
    vi v1((size_t)3, 7);
    assert(base_str == v1.to_str());

    vi v2(v1);
    assert(base_str == v2.to_str());

    vi v3 = v1;
    assert(base_str == v1.to_str());
}

//test basic methods such as push/pop etc
void test2() {
    vi v1((size_t)3, 7);
    v1.push_back(1);
    v1.push_back(2);
    assert(base_str + "1 2 " == v1.to_str());

    v1.pop_back();
    assert(base_str + "1 " == v1.to_str());

    assert(v1.back() == 1);

    assert(!v1.empty());
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    assert(v1.empty());

    vi v2((size_t)3, 7);
    v2.push_back(6);
    assert(v2.size() == 4);
}

//reserve, resize etc
void test3() {
    vi v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    assert(v.capacity() == 4);

    v.reserve(1000);
    assert(v.capacity() >= 1000);

    v.clear();
    assert(v.to_str().empty());

    v.resize(5);
    assert(v.to_str() == "0 0 0 0 0 ");
    v.resize(1, -1);
    assert(v.to_str() == "0 ");
    v.resize(7, -1);
    assert(v.to_str() == "0 -1 -1 -1 -1 -1 -1 ");

    v.assign((size_t)5, 2);
    assert(v.to_str() == "2 2 2 2 2 ");
}

//insert & erase
void test4() {
    vi v;
    v.insert(v.begin(), 4);
    v.insert(v.begin(), 3);
    v.insert(v.begin(), 2);
    v.insert(v.begin(), 1);
    assert(v.to_str() == "1 2 3 4 ");

    v.erase(v.end());
    assert(v.to_str() == "1 2 3 ");
    v.erase(v.begin() + 1);
    assert(v.to_str() == "1 3 ");
}

//test iterators
void test5() {
    std::vector<int> sv;
    sv.push_back(11);
    sv.push_back(31);
    sv.push_back(21);
    vi v(sv.begin(), sv.end());
    assert(v.to_str() == "11 31 21 ");

    std::vector<int> sv1;
    sv1.push_back(111);
    sv1.push_back(311);
    sv1.push_back(211);
    vi v1;
    v1.assign(sv1.begin(), sv1.end());
    assert(v1.to_str() == "111 311 211 ");
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}