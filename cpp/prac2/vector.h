//
// Created by matveich on 12.05.18.
//

#ifndef PRAC2_VECTOR_H
#define PRAC2_VECTOR_H


#include <cstdio>
#include <cstring>
#include <algorithm>


template<typename T>
struct vector {
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator > const_reverse_iterator;

    vector() {
        p = (T *) operator new(sizeof(T) * _capacity);
        _size = 0;
        _capacity = 1;
    }

    vector(size_t n, T value = T()) {
        _size = _capacity = n;
        p = (T *) operator new(sizeof(T) * _capacity);
        __fit();
        for (size_t i = 0; i < _size; i++)
            new (&p[i]) T(value);
    }

    vector(vector const &other) : vector(other._size) {
        for (size_t i = 0; i < _size; i++)
            p[i] = other.p[i];
    }

    template<typename It>
    vector(It first, It last): vector(last - first) {
        __fit();
        for (size_t i = 0; i < _size; i++)
            p[i] = *(first + i);
    }

    ~vector() {
        for (size_t i = 0; i < _capacity; i++)
            p[i].~T();
        operator delete(p);
        _size = 0;
        _capacity = 1;
    }

    vector &operator=(vector const &other) {
        operator delete(p);
        _size = _capacity = other._size;
        __fit();
        p = (T *) operator new(sizeof(T) * _capacity);
        for (size_t i = 0; i < _size; i++)
            p[i] = other.p[i];
        return *this;
    }

    void push_back(T const &x) {
        p[_size++] = x;
        __fit();
    }

    void pop_back() {
        if (_size == 0)
            return;
        p[_size--].~T();
        __fit();
    }

    T &back() {
        return p[_size - 1];
    }

    T const &back() const {
        return p[_size - 1];
    }

    bool empty() const {
        return _size == 0;
    }

    T &operator[](size_t n) {
        return *p[n];
    }

    T const &operator[](size_t n) const {
        return *p[n];
    }

    size_t size() const {
        return _size;
    }

    T *data() {
        return p;
    }

    T const *data() const {
        return p;
    }

    void reserve(size_t n) {
        if (n <= _capacity)
            return;
        auto tmp = _size;
        _size = n;
        __fit();
        _size = tmp;
    }

    size_t capacity() const {
        return _capacity;
    }

    void shrink_to_fit() {
        __fit();
    }

    void clear() {
        for (size_t i = 0; i < _capacity; i++)
            p[i].~T();
        _size = 0;
        __fit();
    }

    iterator insert(const_iterator pos, T const& value) {
        _size++;
        size_t ind = pos - begin();
        __fit();
        for (size_t i = _size - 1; i > ind; i--)
            p[i] = p[i - 1];
        p[ind] = value;
        return p;
    }

    iterator erase(const_iterator pos) {
        size_t ind = pos - p;
        for (size_t i = ind; i < _size - 1; i++)
            p[i] = p[i + 1];
        _size--;
        __fit();
    }

    void resize(size_t n, T value=T()) {
        if (n < _size) {
            _size = n;
        }
        else {
            for (size_t i = _size; i < n; i++)
                push_back(value);
            _size = n;
        }
        __fit();
    }

    void assign(size_t n, T value=T()) {
        _size = n;
        __fit();
        for (size_t i = 0; i < n; i++)
            p[i] = value;
    }

    template<typename It>
    void assign(It first, It last) {
        _size = last - first;
        __fit();
        for (size_t i = 0; i < _size; i++)
            p[i] = *(first + i);
    }

    iterator begin() {
        return p;
    }

    const_iterator begin() const {
        return p;
    }

    iterator end() {
        return p + _size;
    }

    const_iterator end() const {
        return p + _size;
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return reverse_iterator(begin());
    }

    void print() {
        for (size_t i = 0; i < _size; i++)
            std::cout << p[i] << " ";
        std::cout << std::endl;
    }

    std::string to_str() {
        std::string s;
        for (size_t i = 0; i < _size; i++) {
            s += std::to_string(p[i]) + " ";
        }
        return s;
    }

private:
    T *p;
    size_t _size, _capacity;
    const unsigned int FIT_COEF = 2;
    const unsigned int SHRINK_COEF = 4;

    bool __check_fit() {
        return _size == _capacity || _size * SHRINK_COEF <= _capacity;
    }

    void __fit() {
        if (_capacity <= 0)
            _capacity = 1;
        if (_capacity < _size) // just pretty hack
            _capacity = _size;
        if (!__check_fit())
            return;
        size_t new_capacity = _size == _capacity ? _capacity * FIT_COEF : _capacity / FIT_COEF;
        auto p1 = new int[new_capacity];
        memcpy(p1, p, std::min(_capacity, new_capacity) * sizeof(T));
        delete[] p;
        p = p1;
        _capacity = new_capacity;
    }
};
//TODO: хуйня с memcpy; неправильно аллоцируется в конструкторе
//TODO
/*void swap(vector& a, vector& b) {
    auto tmp = a.data();
    a.data() = b.data();
    b.data() = tmp;

}*/

#endif //PRAC2_VECTOR_H
