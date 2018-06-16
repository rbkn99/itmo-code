//
// Created by matveich on 05.06.18.
//

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <vector>
#include <iostream>
#include <queue>
#include <cassert>
#include <cstring>
#include <algorithm>
#include "bit_sequence.h"

class tree {
public:
    typedef unsigned long long ull;

    tree();

    void update_dict(const char *data, size_t data_size);

    void build_by_freq_dict(const char *data, size_t data_size);

    void build();

    std::vector<char> get_dict();

    bit_sequence *compress(const char *data, size_t data_size, bit_sequence &offset);

    bit_sequence *decompress(const char *data, size_t data_size, bit_sequence &offset, bool is_last_chunk);

    ~tree();

    template<typename T = size_t>
    static char u_to_char(T x) {
        return static_cast<char>(x - 128u);
    }

    template<typename T = size_t>
    static T char_to_u(char x) {
        return static_cast<T>(x) + 128u;
    }

private:
    const size_t SIGMA_SIZE = 256;
    //const size_t CHAR_SIZE = sizeof(char);
    //const size_t ULL_SIZE = sizeof(ull);

    std::vector<ull> freq_dict;
    std::vector<bit_sequence> dict;
    std::vector<bit_sequence> bs_repr;

    char expected_offset;

    struct vertex {
        vertex *left;
        vertex *right;
        ull value;
        int key;

        vertex(vertex *l, vertex *r, ull val, int key = -1) :
                left(l),
                right(r),
                value(val),
                key(key) {}

        vertex(ull val, int key = -1) :
                left(nullptr),
                right(nullptr),
                value(val),
                key(key) {}

        ~vertex() {
            if (left)
                delete left;
            if (right)
                delete right;
            left = right = nullptr;
        }
    } *head;

    size_t max_tree_depth;

    void build_tree();

    void build_dict(vertex *v, bit_sequence &seq, size_t depth);

    char calc_data_size();

    char *ull_to_char(ull x);

    void insert_ull(std::vector<char> &v, ull x);

    bit_sequence uint8_to_bitseq(uint8_t c, size_t length);
};


#endif //HUFFMAN_TREE_H
