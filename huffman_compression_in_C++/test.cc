#include <iostream>
#include <fstream>
#include "huffman.h"
#include "pqueue.h"
#include "bstream.h"
using namespace std;


// testing if the freq table is made
int main(int argc, char const *argv[]) {
  Huffman test;
	std::ifstream ifs(argv[1], std::ios::in |
                    std::ios::binary);
	std::ofstream ofs(argv[2], std::ios::out |
                    std::ios::trunc |
                    std::ios::binary);
	test.Compress(ifs, ofs);
}
