//
// Created by matveich on 15.06.18.
//

#ifndef HUFFMAN_BASIC_CODER_H
#define HUFFMAN_BASIC_CODER_H

#include <iostream>
#include <fstream>
#include "tree.h"

class basic_coder {
protected:

    std::ifstream src_file;
    std::ofstream dst_file;

    size_t buffer_size;

    tree *h_tree;

    basic_coder(std::string &src, std::string &dst, size_t buf_sz);

    ~basic_coder();
};


#endif //HUFFMAN_BASIC_CODER_H
