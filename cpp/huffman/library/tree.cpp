//
// Created by matveich on 05.06.18.
//

#include "tree.h"

tree::tree() {
    freq_dict.resize(SIGMA_SIZE);
    dict.resize(SIGMA_SIZE);
    bs_repr.resize(SIGMA_SIZE);
    head = nullptr;
    expected_offset = 0;
    max_tree_depth = 0;

    for (size_t i = 0; i < SIGMA_SIZE; i++) {
        bs_repr[i] = bit_sequence(1);
        for (size_t j = 0; j < 8; j++) {
            bs_repr[i].push(((i >> (7 - j)) & 1) == 1);
        }
    }
}

void tree::update_dict(const char *data, size_t data_size) {
    for (size_t i = 0; i < data_size; ++i)
        ++freq_dict[char_to_u(data[i])];
}

tree::~tree() {
    delete head;
}

void tree::build_tree() {
    auto comp = [](vertex *a, vertex *b) { return a->value > b->value; };
    std::priority_queue<vertex *, std::vector<vertex *>, decltype(comp)> q(comp);
    for (size_t i = 0; i < freq_dict.size(); i++) {
        if (freq_dict[i] > 0)
            q.push(new vertex(freq_dict[i], static_cast<int>(i)));
    }
    if (q.size() == 0)
        return;
    else if (q.size() == 1) {
        q.push(new vertex(0, q.top()->key));
    }
    while (q.size() > 1) {
        auto l = q.top();
        q.pop();
        auto r = q.top();
        q.pop();
        q.push(new vertex(l, r, l->value + r->value));
    }
    head = q.top();
    q.pop();
}

void tree::build_dict(vertex *v, bit_sequence &seq, size_t depth) {
    if (v->key != -1) {
        dict[v->key] = seq;
        if (depth > max_tree_depth) {
            max_tree_depth = depth;
            if (max_tree_depth > SIGMA_SIZE)
                throw std::runtime_error("max tree depth is reached");
        }
        return;
    }
    seq.push(false);
    build_dict(v->left, seq, depth + 1);
    seq.set(seq.bit_size() - 1, true);
    build_dict(v->right, seq, depth + 1);
    seq.pop_bit();
}

void tree::build() {
    build_tree();
    if (!head)
        return;
    bit_sequence tmp(8);
    build_dict(head, tmp, 0);
}

char *tree::ull_to_char(tree::ull x) {
    char *result = new char[8];
    for (size_t i = 0; i < 8; ++i)
        result[i] = u_to_char((x >> ((7 - i) * 8)) & 0xFF);
    return result;
}

char tree::calc_data_size() {
    ull data_size = 0;
    for (size_t i = 0; i < SIGMA_SIZE; ++i)
        data_size += freq_dict[i] * dict[i].bit_size();
    return expected_offset = static_cast<char>((8 - data_size % 8) % 8);
}

void tree::insert_ull(std::vector<char> &v, tree::ull x) {
    char *char_val = ull_to_char(x);
    v.insert(v.end(), char_val, char_val + 8);
    delete[] char_val;
}

std::vector<char> tree::get_dict() {
    // get actual _bit_size of freq dict
    int size = 0;
    for (size_t i = 0; i < freq_dict.size(); ++i) {
        if (freq_dict[i] > 0)
            size++;
    }
    std::vector<char> out_dict;
    out_dict.reserve(static_cast<size_t>(size) * 9 + 2);
    out_dict.push_back(u_to_char<int>(size));
    for (size_t i = 0; i < freq_dict.size(); i++) {
        if (freq_dict[i] != 0) {
            out_dict.push_back(u_to_char(i));
            insert_ull(out_dict, freq_dict[i]);
        }
    }
    out_dict.push_back(calc_data_size());
    return out_dict;
}

void tree::build_by_freq_dict(const char *data, size_t data_size) {
    size_t i = 0;
    for (; i + 9 <= data_size; i += 9) {
        size_t ind = char_to_u(data[i]);
        for (size_t j = 0; j < 8; j++) {
            freq_dict[ind] += (char_to_u<ull>(data[i + 1 + j]) << (56 - 8 * j));
        }
    }
    expected_offset = data[i];
    build();
}

bit_sequence tree::uint8_to_bitseq(uint8_t c, size_t length) {
    bit_sequence bs(1);
    for (size_t i = 0; i < length; ++i)
        bs.push(bit_sequence::get_bit<uint8_t>(c, i));
    return bs;
}

bit_sequence *tree::compress(const char *data, size_t data_size, bit_sequence &offset) {
    bit_sequence *compressed_data = new bit_sequence(data_size * max_tree_depth / 8 + 1);
    compressed_data->append(offset);
    offset.clear();
    //offset.~bit_sequence();
    for (size_t i = 0; i < data_size; i++) {
        compressed_data->append(dict[char_to_u(data[i])]);
    }
    //std::cout << compressed_data.to_string() << std::endl;
    if (compressed_data->size() > 0)
        offset = uint8_to_bitseq(compressed_data->get_word(compressed_data->size() - 1),
                                 compressed_data->bit_size() % 8);
    while (compressed_data->bit_size() % 8 != 0)
        compressed_data->pop_bit();
    return compressed_data;
}

bit_sequence *tree::decompress(const char *data, size_t data_size, bit_sequence &offset, bool is_last_chunk) {
    size_t bit_size = data_size * 8, result_pos = 0;
    bit_sequence *result = new bit_sequence(bit_size * 8 + 2);
    if (!head)
        return result;
    if (is_last_chunk)
        bit_size -= expected_offset;
    vertex *p = head;
    for (size_t i = 0; i < offset.bit_size(); i++)
        p = (offset[i] ? p->right : p->left);
    offset.clear();
    for (size_t i = 0; i < bit_size; ++i) {
        if (p->key != -1) {
            result->set_byte(result_pos++, bs_repr[p->key].get_data()[0] ^ (uint8_t) 128u);
            p = head;
        }
        if (bit_sequence::get_bit(data[i >> 3], i & 0b111))
            p = p->right;
        else
            p = p->left;
    }
    if (p->key != -1) {
        result->set_byte(result_pos, bs_repr[p->key].get_data()[0] ^ (uint8_t) 128u);
    }
    else {
        size_t c = 0;
        while (p->left) {
            c++;
            p = p->left;
        }
        for (size_t i = 0; i < dict[p->key].bit_size() - c; i++) {
            offset.push(dict[p->key][i]);
        }
    }
    return result;
}