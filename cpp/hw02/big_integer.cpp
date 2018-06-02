//
// Created by matveich on 30.03.18.
//

#include "big_integer.h"

const big_integer::ui BASE = 32;
const big_integer::ui MAX_INT = UINT32_MAX;
const big_integer::ull SHIFT_BASE = ((big_integer::ull) 1 << BASE);
const big_integer::ui BASE_10 = 1000000000;

size_t big_integer::length() const {
    return number.size();
}

template <typename T>
big_integer::ui big_integer::cast_to_ui(T x) const {
    return static_cast<ui>(x & MAX_INT);
}

big_integer big_integer::abs() const {
    return sign ? -(*this) : *this;
}

big_integer::big_integer() :
        sign(false),
        number({0})
{}

big_integer::big_integer(int source) :
        sign(source < 0),
        number({cast_to_ui(source)})
{}

big_integer::big_integer(big_integer const &source) :
        sign(source.sign),
        number(source.number)
{
    shrink();
}

big_integer::big_integer(std::string source):
        sign(false),
        number({0})
{
    bool _sign = (source[0] == '-');
    size_t it = (_sign ? 1 : 0);
    for (; it + 9 <= source.length(); it += 9)
        *this = *this * BASE_10 + stoi(source.substr(it, 9));
    if (it < source.length())
        *this = *this * static_cast<ui>(pow(10, source.length() - it))
                + stoi(source.substr(it));
    if (_sign)
        *this = -(*this);
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
    if (*this == 0)
        return *this;
    big_integer res;
    res.number.clear();
    std::transform(number.begin(), number.end(),
                   std::back_inserter(res.number),
                   [](ui x) -> ui{ return ~x; });
    res.shrink();
    res += 1;
    res.sign = !sign;
    return res;
}

big_integer &big_integer::operator+=(big_integer const &rhs) {
    ull cf = 0, sum = 0;
    big_integer result;
    result.number.clear();
    result.sign = sign;
    auto n = std::max(length(), rhs.length()) + 2;
    for (size_t it = 0; it < n; it++) {
        sum = static_cast<ull>((*this)[it]) + rhs[it] + cf;
        result.number.push_back(cast_to_ui(sum));
        cf = sum >> BASE;
    }
    if (sign != rhs.sign && abs() <= rhs.abs()) {
        if (abs() == rhs.abs())
            result.sign = false;
        else
            result.sign = !result.sign;
    }
    result.shrink();
    return *this = result;
}

big_integer &big_integer::operator-=(big_integer const &rhs) {
    return *this += -rhs;
}

big_integer operator+(big_integer a, big_integer const &b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const &b) {
    return a -= b;
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

big_integer big_integer::__mul_long_short(big_integer::ui x, size_t offset) const {
    big_integer result;
    result.sign = sign;
    size_t n = length() + offset + 2;
    result.number.resize(n, sign ? UINT32_MAX : 0);
    ull mul = 0, cf = 0;
    for (size_t i = offset; i < n; i++) {
        mul = static_cast<ull>((*this)[i - offset]) * x + cf;
        result.number[i] = cast_to_ui(mul);
        cf = mul >> BASE;
    }
    result.shrink();
    return result;
}

big_integer big_integer::__quotient(big_integer::ui x) const {
    big_integer result;
    result.sign = sign;
    size_t n = length();
    result.number.resize(n, sign ? UINT32_MAX : 0);
    ull div = 0, cf = 0;
    for (int i = static_cast<int>(n - 1); i >= 0; i--) {
        div = static_cast<ull>((*this)[i]) + (cf << BASE);
        result.number[i] = cast_to_ui(div / x);
        cf = div % x;
    }
    result.shrink();
    return result;
}

big_integer::ui big_integer::__remainder(big_integer::ui x) const {
    size_t n = length();
    ull cf = 0;
    for (int i = static_cast<int>(n - 1); i >= 0; i--)
        cf = ((cf << BASE) + (*this)[i]) % x;
    return cast_to_ui(cf);
}

std::pair<big_integer, big_integer> big_integer::div_mod(big_integer const &rhs) {
    if (rhs == 0)
        throw "division by zero";
    if (rhs.length() > length())
        return std::make_pair(0, *this);
    if (rhs.length() == 1)
        return std::make_pair(__quotient(rhs[0]), __remainder(rhs[0]));
    big_integer b = rhs;

    // normalize b
    ui k = static_cast<ui>(ceil(log2((static_cast<double>(cast_to_ui(SHIFT_BASE >> 1)) / b.number.back()))));
    b <<= k;
    (*this) <<= k;
    size_t m = length() - b.length();
    size_t n = b.length();
    big_integer q;
    q.number.resize(m + 1);
    b <<= (BASE * m);
    if (*this > b) {
        q.number[m] = 1;
        *this -= b;
    }

    for (int j = static_cast<int>(m - 1); j >= 0; j--) {
        q.number[j] = cast_to_ui(((static_cast<ull>((*this)[n + j]) << BASE) + (*this)[n + j - 1]) / b.number.back());
        b >>= BASE;
        *this -= b.__mul_long_short(q[j], 0);

        // is executed twice in the worst case
        while (sign) {
            q.number[j]--;
            *this += b;
        }
    }
    q.shrink();
    shrink();
    return std::make_pair(q, *this >> k);
}

big_integer &big_integer::operator*=(big_integer const &rhs) {
    big_integer storage = *this, rhs_copy = rhs;
    bool s1 = sign, s2 = rhs_copy.sign;
    if (s1) storage = -storage;
    if (s2) rhs_copy = -rhs_copy;
    *this = 0;
    for (size_t i = 0; i < rhs_copy.length(); i++)
        *this += storage.__mul_long_short(rhs_copy[i], i);
    shrink();
    if (s1 != s2) *this = -(*this);
    return *this;
}

big_integer &big_integer::operator/=(big_integer const &rhs) {
    bool s1 = sign, s2 = rhs.sign;
    if (s1) *this = -(*this);
    *this = !s2 ? div_mod(rhs).first : div_mod(-rhs).first;
    if (s1 != s2) *this = -(*this);
    return *this;
}

big_integer &big_integer::operator%=(big_integer const &rhs) {
    bool s1 = sign, s2 = rhs.sign;
    if (s1) *this = -(*this);
    *this = !s2 ? div_mod(rhs).second : div_mod(-rhs).second;
    if (s1) *this = -(*this);
    return *this;
}

bool operator==(big_integer const &a, big_integer const &b) {
    if (a.sign != b.sign || a.length() != b.length())
        return false;
    for (int i = static_cast<int>(a.length()) - 1; i >= 0; i--) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

bool operator!=(big_integer const &a, big_integer const &b) {
    return !(a == b);
}

bool operator<(big_integer const &a, big_integer const &b) {
    if (a.sign != b.sign)
        return a.sign > b.sign;
    if (a.length() != b.length())
        return a.sign ^ (a.length() < b.length());
    for (int i = static_cast<int>(a.length()) - 1; i >= 0; i--) {
        if (a[i] != b[i])
            return a.sign ^ (a[i] < b[i]);
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

big_integer big_integer::operator~() const {
    return -(*this) - 1;
}

template<class FunctorT>
big_integer& big_integer::apply_bitwise_operation(big_integer const & rhs, FunctorT functor) {
    for (size_t i = 0; i < length(); i++)
        number[i] = functor(number[i], rhs[i]);
    sign = functor(sign, rhs.sign);
    return *this;
}

big_integer& big_integer::operator&=(big_integer const &rhs) {
    return apply_bitwise_operation(rhs, std::bit_and<ui>());
}

big_integer operator&(big_integer a, big_integer const &b) {
    return a &= b;
}


big_integer& big_integer::operator|=(big_integer const &rhs) {
    return apply_bitwise_operation(rhs, std::bit_or<ui>());
}

big_integer operator|(big_integer a, big_integer const &b) {
    return a |= b;
}

big_integer& big_integer::operator^=(big_integer const &rhs) {
    return apply_bitwise_operation(rhs, std::bit_xor<ui>());
}

big_integer operator^(big_integer a, big_integer const &b) {
    return a ^= b;
}

big_integer& big_integer::operator<<=(int rhs) {
    if (rhs < 0)
        throw "error! right value is negative";
    bool negative_flag = sign;
    if (rhs % BASE == 0) {
        std::vector<int> zeros(rhs / BASE, negative_flag ? MAX_INT : 0);
        number.insert(number.begin(), zeros.begin(), zeros.end());
        return *this;
    }
    if (negative_flag)
        *this = -(*this);
    big_integer result;
    result.number.resize(rhs / BASE);
    rhs %= BASE;
    ui cf = 0;
    for (auto &x: number) {
        result.number.push_back((x << rhs) + cf);
        cf = cast_to_ui(x >> (BASE - rhs));
    }
    if (cf != 0)
        result.number.push_back(cf);
    if (negative_flag)
        result = -result;
    result.shrink();
    return *this = result;
}

big_integer operator<<(big_integer a, int b) {
    return a <<= b;
}

big_integer& big_integer::operator>>=(int rhs) {
    if (rhs < 0)
        throw "error! right value is negative";
    if (rhs % BASE == 0) {
        number.erase(number.begin(), number.begin() + (rhs / BASE));
        return *this;
    }
    bool negative_flag = sign;
    if (negative_flag)
        *this = -(*this);
    big_integer result;
    result.number.clear();
    int gap = rhs / BASE;
    rhs %= BASE;
    ui cf = 0;
    for (size_t i = length() - 1; static_cast<int>(i) >= gap; i--) {
        result.number.push_back(((*this)[i] >> rhs) + cf);
        cf = cast_to_ui((*this)[i] << (BASE - rhs));
    }
    std::reverse(result.number.begin(), result.number.end());
    result.sign = sign;
    if (negative_flag)
        result = -result - 1;
    return *this = result;
}

big_integer operator>>(big_integer a, int b) {
    return a >>= b;
}

big_integer::ui big_integer::operator[](size_t pos) const {
    if (pos < length())
        return number[pos];
    return sign ? MAX_INT : 0;
}

void big_integer::shrink() {
    while (length() > 1 && ((sign && number.back() == MAX_INT) || (!sign && number.back() == 0)))
        number.pop_back();
}

std::string to_string(big_integer const &source) {
    if (source == 0)
        return "0";
    std::string result = "";
    auto src_copy = (source.sign ? -source : source);
    while (src_copy > 0) {
        auto slice = (src_copy % BASE_10)[0];
        for (size_t i = 0; i < 9; i++) {
            result.push_back('0' + char(slice % 10));
            slice /= 10;
        }
        src_copy /= BASE_10;
    }
    while (!result.empty() && result.back() == '0')
        result.pop_back();
    if (source.sign)
        result.push_back('-');
    std::reverse(result.begin(), result.end());
    return result;
}