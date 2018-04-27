//
// Created by matveich on 30.03.18.
//

#ifndef HW02_BIG_INTEGER_H
#define HW02_BIG_INTEGER_H

#include <algorithm>
#include <string>
#include <vector>
#include <climits>

using namespace std;

typedef unsigned int ui;
typedef unsigned long long ull;

class big_integer {
public:
    big_integer();

    big_integer(big_integer const &);

    big_integer(int);

    explicit big_integer(string);

    ~big_integer();

    big_integer &operator=(big_integer const &);

    big_integer &operator+=(big_integer const &);

    big_integer &operator-=(big_integer const &);

    big_integer &operator*=(big_integer const &);

    big_integer &operator/=(big_integer const &);

    big_integer &operator%=(big_integer const &);

    big_integer operator+() const;

    big_integer operator-() const;

    big_integer operator~() const;

    int operator[](size_t i) const;

    friend string to_string(big_integer const &);

    friend big_integer _abs(big_integer const &);

    friend bool operator==(big_integer const &a, big_integer const &b);

    friend bool operator!=(big_integer const &a, big_integer const &b);

    friend bool operator<(big_integer const &a, big_integer const &b);

    friend bool operator>(big_integer const &a, big_integer const &b);

    friend bool operator<=(big_integer const &a, big_integer const &b);

    friend bool operator>=(big_integer const &a, big_integer const &b);

    size_t length() const {
        return number.size();
    };

    bool get_sign() const {
        return sign;
    };

private:
    template <typename T>
    ui cast_to_ui(T);

    /*template <typename T>
    ui cast_to_ull(T);*/

    const ui BASE = 32;
    const ull SHIFT_BASE = ((ull)1 << BASE);
    vector<ui> number;
    bool sign;
    pair<big_integer, big_integer> div_mod(big_integer const &a);

    friend big_integer mul_long_short(big_integer const &a, ui x, size_t offset);
    int comp(big_integer& x, big_integer& y, bool is_y_reversed=false);
    void reverse_number();
    void shrink();
    void twos_completment();
};

big_integer operator+(big_integer a, big_integer const &b);

big_integer operator-(big_integer a, big_integer const &b);

big_integer operator*(big_integer a, big_integer const &b);

big_integer operator/(big_integer a, big_integer const &b);

big_integer operator%(big_integer a, big_integer const &b);


#endif //HW02_BIG_INTEGER_H
