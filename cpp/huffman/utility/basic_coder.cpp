//
// Created by matveich on 15.06.18.
//

#include "basic_coder.h"

basic_coder::basic_coder(std::string &src, std::string &dst, size_t buf_sz) :
        src_file(src, std::ios::in | std::ios::binary),
        dst_file(dst, std::ios::out | std::ios::binary),
        buffer_size(buf_sz) {
    if (!src_file.is_open())
        throw std::runtime_error("Source file doesn't exist");
    if (!dst_file.is_open())
        throw std::runtime_error("Destination file name is invalid");
    h_tree = new tree();
}

basic_coder::~basic_coder() {
    delete h_tree;
}