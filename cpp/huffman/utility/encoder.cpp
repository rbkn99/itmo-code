//
// Created by matveich on 08.06.18.
//

#include "encoder.h"


encoder::encoder(std::string &src, std::string &dst) : basic_coder(src, dst, 8 * 1024 * 1024) {}

void encoder::count_bytes() {
    auto buffer = new char[buffer_size];
    while (src_file) {
        src_file.read(buffer, buffer_size);
        h_tree->update_dict(buffer, static_cast<size_t>(src_file.gcount()));
    }
    delete[] buffer;
}

void encoder::compress() {
    bit_sequence bs(1);
    auto buffer = new char[buffer_size];
    while (src_file) {
        src_file.read(buffer, buffer_size);
        bit_sequence *compressed = h_tree->compress(buffer, static_cast<size_t>(src_file.gcount()), bs);
        dst_file.write((char *) compressed->get_data(), compressed->size());
        delete compressed;
    }
    delete[] buffer;
    if (bs.bit_size() > 0)
        dst_file.write((char *) bs.get_data(), 1);
}

void encoder::encode() {
    count_bytes();
    h_tree->build();
    auto dict = h_tree->get_dict();
    dst_file.write(dict.data(), dict.size());
    src_file.clear();
    src_file.seekg(0, std::ifstream::beg);
    compress();
}