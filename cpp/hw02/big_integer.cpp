//
// Created by matveich on 30.03.18.
//

#include "big_integer.h"

big_integer::big_integer() {
    number.push_back(0);
    sign = false;
}

big_integer::big_integer(int source) {
    sign = source < 0;
    number.push_back(cast_to_ui(source));
}

big_integer::big_integer(big_integer const &source) {
    number = source.number;
    sign = source.sign;
    shrink();
}

big_integer::big_integer(string source) {
    if (source.empty())
        *this = big_integer();
    sign = (source[0] == '-');
    size_t it = sign ? 1 : 0;
    ui buffer = 0, pow_coef = 1;
    char digit;
    for (; it < source.size(); it++) {
        digit = source[it] - '0';
        if (UINT32_MAX - digit < buffer) {
            number.push_back(buffer);
            buffer = 0;
            pow_coef = 1;
        }
        buffer += digit * pow_coef;
        pow_coef *= 10;
    }
    reverse_number();
    shrink();
}

big_integer::~big_integer() {
    number.clear();
    sign = false;
}

big_integer &big_integer::operator=(big_integer const &other) {
    number = other.number;
    sign = other.sign;
    return *this;
}

big_integer big_integer::operator+() const {
    return *this;
}

big_integer big_integer::operator-() const {
    big_integer res;
    for (size_t it = 0; it < number.size(); it++)
        res.number.push_back(~number[it]);
    res += 1;
    res.sign = !sign;
    res.shrink();
    return res;
}

big_integer &big_integer::operator+=(big_integer const &rhs) {
    if (!sign && rhs.sign)
        return *this = *this - -rhs;
    if (sign && !rhs.sign)
        return *this = -(-*this - rhs);
    if (sign && rhs.sign)
        return *this = -(-*this + -rhs);
    ull cf = 0, sum = 0;
    big_integer result;
    result.number.clear();
    auto n = max(length(), rhs.length()) + 2;
    for (size_t it = 0; it < n; it++) {
        sum = (*this)[it] + rhs[it] + cf;
        result.number.push_back(cast_to_ui(sum));
        cf = sum >> BASE;
    }
    result.shrink();
    return *this = result;
}

big_integer &big_integer::operator-=(big_integer const &rhs) {
    if (!sign && rhs.sign)
        return *this = *this + -rhs;
    if (sign && !rhs.sign)
        return *this = -(-*this + rhs);
    if (sign && rhs.sign)
        return *this = -(-*this - -rhs);
    ull cf = 0, tmp_number = 0;
    auto min_size = min(length(), rhs.length());
    auto max_size = max(length(), rhs.length());

    for (size_t i = 0; i < min_size; i++) {
        tmp_number = number[i] + rhs.number[i] + cf;
        number[i] = cast_to_ui(tmp_number % SHIFT_BASE);
        cf = cast_to_ui(tmp_number / SHIFT_BASE);
    }
    for (auto i = min_size; i < max_size; i++) {
        if (rhs.length() == max_size) {
            tmp_number = rhs.number[i] + cf;
            number.push_back(cast_to_ui(tmp_number % SHIFT_BASE));
        }
        else {
            tmp_number = number[i] + cf;
            number[i] = cast_to_ui(tmp_number % SHIFT_BASE);
        }
        cf = cast_to_ui(tmp_number / SHIFT_BASE);
    }
    if (cf != 0)
        number.push_back(cast_to_ui(cf));
    shrink();
    return *this;
}

big_integer operator+(big_integer a, big_integer const &b) {
    return a += b;
    /*if (!a.get_sign() && ! b.get_sign())
        return a += b;
    if (!a.get_sign() && b.get_sign())
        return a -= -b;
    if (a.get_sign() & !b.get_sign())
        return -(a -= b);
    return -(a += b);*/
}

big_integer operator-(big_integer a, big_integer const &b) {
    return a -= b;
    /*if (!a.get_sign() && ! b.get_sign())
        return a -= b;
    if (!a.get_sign() && b.get_sign())
        return a += -b;
    if (a.get_sign() & !b.get_sign())
        return -(a += b);
    return -(a -= b);*/
}

big_integer operator*(big_integer a, big_integer const &b) {
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const &b) {
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const &b) {
    return a %= b;
}

big_integer mul_long_short(big_integer const &a, ui x, size_t offset) {
    big_integer result;
    result.sign = a.sign;
    for (size_t i = 0; i < a.length() + offset - 1; i++)
        result.number.push_back(0);
    int tmp = 0, carry = 0;
    for (size_t i = offset; i < a.length() + offset; i++) {
        tmp = a.number[i - offset] * x + carry;
        result.number[i] = tmp % 10;
        carry = tmp / 10;
    }
    if (carry > 0)
        result.number.push_back(carry);
    return result;
}

// optimization, using only in division function
// x is represented in strict order, y - in reversed, if flag is true
// important! comparison by absolute value
// return value: 1 if x > y, 0 if x == y, -1 otherwise
int big_integer::comp(big_integer &x, big_integer &y, bool is_y_reversed) {
    if (x.length() < y.length())
        return -1;
    if (x.length() > y.length())
        return 1;
    for (int i = 0; i < static_cast<int>(x.length()); i++) {
        if (is_y_reversed) {
            if (x[i] < y[y.length() - i - 1])
                return -1;
            if (x[i] > y[y.length() - i - 1])
                return 1;
        }
        else {
            if (x[i] < y[i])
                return -1;
            if (x[i] > y[i])
                return 1;
        }
    }
    return 0;
}

pair<big_integer, big_integer> big_integer::div_mod(big_integer const &rhs) {
    if (rhs == 0)
        throw "division by zero";

    // lets do some optimizations
    big_integer a = _abs(rhs);
    big_integer this_abs = _abs(*this);
    big_integer chunk, result;

    if (a > this_abs)
        return make_pair(0, *this);
    if (a == this_abs || a == 1) {
        result = 1;
        if (a == 1)
            result = *this;
        result.sign = sign ^ rhs.sign;
        return make_pair(result, 0);
    }

    chunk.number.clear();
    result.number.clear();
    int it = static_cast<int>(length() - 1);

    while (it >= 0) {
        while (it >= 0) {
            chunk.number.push_back(number[it]);
            it--;
            if (chunk.length() >= a.length())
                break;
            result.number.push_back(0);
        }
        if (it >= 0 && comp(a, chunk) == 1) {
            chunk.number.push_back(number[it]);
            result.number.push_back(0);
            it--;
        }
        //chunk.shrink();
        reverse(chunk.number.begin(), chunk.number.end());
        int c = 0;
        big_integer tmp = 0;
        while ((tmp += a) <= chunk)
            c++;
        if (c > 0) {
            c--;
            tmp -= a;
        }
        if (!tmp.sign)
            chunk -= tmp;
        else
            chunk += tmp;
        result.number.push_back(c);
        reverse(chunk.number.begin(), chunk.number.end());
        if (chunk == 0)
            chunk.number.clear();
    }
    reverse(result.number.begin(), result.number.end());
    result.shrink();
    result.sign = sign ^ rhs.sign;
    chunk.sign = sign ^ rhs.sign;
    if (chunk.number.size() == 0)
        chunk = 0;
    return make_pair(result, chunk);
}

big_integer &big_integer::operator*=(big_integer const &rhs) {
    big_integer storage = *this;
    *this = 0;

    for (size_t i = 0; i < rhs.length(); i++) {
        *this += mul_long_short(storage, rhs.number[i], i);
    }
    sign = (sign != rhs.sign);
    shrink();
    return *this;
}

big_integer &big_integer::operator/=(big_integer const &rhs) {
    bool s = sign;
    *this = div_mod(rhs).first;
    sign = s != rhs.sign;
    shrink();
    return *this;
}

big_integer &big_integer::operator%=(big_integer const &rhs) {
    *this = div_mod(rhs).second;
    shrink();
    return *this;
}

big_integer _abs(big_integer const &a) {
    big_integer res = a;
    res.sign = false;
    return res;
}

bool operator==(big_integer const &a, big_integer const &b) {
    if ((a.sign != b.sign && (a.number.back() != 0 || b.number.back() != 0)) || a.number.size() != b.number.size())
        return false;
    for (int i = static_cast<int>(a.length()) - 1; i >= 0; i--) {
        if (a.number[i] != b.number[i])
            return false;
    }
    return true;
}

bool operator!=(big_integer const &a, big_integer const &b) {
    return !(a == b);
}

bool operator<(big_integer const &a, big_integer const &b) {
    if (a.sign && !b.sign)
        return true;
    if (!a.sign && b.sign)
        return false;
    if (a.number.size() < b.number.size())
        return !a.sign;
    if (a.number.size() > b.number.size())
        return a.sign;
    for (int i = static_cast<int>(a.length()) - 1; i >= 0; i--) {
        if (a.number[i] < b.number[i]) {
            return !a.sign;
        }
        if (a.number[i] > b.number[i])
            return a.sign;
    }
    return false;
}

bool operator>(big_integer const &a, big_integer const &b) {
    return !(a < b || a == b);
}

bool operator<=(big_integer const &a, big_integer const &b) {
    return a < b || a == b;
}

bool operator>=(big_integer const &a, big_integer const &b) {
    return a > b || a == b;
}

int big_integer::operator[](size_t pos) const {
    if (pos < length())
        return number[pos];
    if (sign)
        return UINT32_MAX;
    return 0;
}

void big_integer::shrink() {
    while (length() > 1 && number.back() == 0)
        number.pop_back();
}

void big_integer::reverse_number() {
    reverse(number.begin(), number.end());
}

void big_integer::twos_completment() {
    for (size_t it = 0; it < number.size(); it++)
        number[it] = ~number[it];
}

template <typename T>
ui big_integer::cast_to_ui(T x) {
    return static_cast<ui>(x & UINT32_MAX);
}

string to_string(big_integer const &source) {
    string str_bi;
    big_integer source_copy = source;
    if (source.sign && source != 0) {
        source_copy = -source;
        str_bi.push_back('-');
    }
    int i = static_cast<int>(source_copy.length()) - 1;
    while (i > 0 && source_copy.number[i] == 0) i--;
    for (; i >= 0; i--)
        str_bi.push_back(static_cast<char>('0' + source_copy.number[i]));
    return str_bi;
}