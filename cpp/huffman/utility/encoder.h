//
// Created by matveich on 08.06.18.
//

#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include "basic_coder.h"


class encoder : basic_coder {
public:
    encoder(std::string &src, std::string &dst);

    void encode();

private:
    void count_bytes();

    void compress();
};


#endif //HUFFMAN_ENCODER_H
