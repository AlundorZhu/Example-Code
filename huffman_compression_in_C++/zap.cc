#include <fstream>
#include <iostream>

#include "bstream.h"
#include "huffman.h"
#include "pqueue.h"

void read_args(int argc, char **argv, std::string &program_name,
               std::string &input_file, std::string &output_file) {
  program_name = argv[0];
  if (argc < 3) {  // validation if under 3 args
    std::cerr << "Usage: " << program_name << " <inputfile> <zapfile>";
    exit(1);
  }
  if (argc > 3) {  // validation if over 3 args
    std::cerr << "Usage: " << program_name << " <inputfile> <zapfile>";
    exit(1);
  }
  input_file = argv[1];
  std::ifstream valid;
  valid.open(input_file);
  if (!(valid)) {  // checks whether the file is valid
    std::cerr << "Error: cannot open input file " << input_file;
    exit(1);
  }
  output_file = argv[2];
  std::ofstream valid2;
  valid2.open(output_file);
  if (!(valid2)) {  // checks whether the file is valid
    std::cerr << "Error: cannot open zap file " << output_file;
    exit(1);
  }
}

int main(int argc, char **argv) {
  std::string program_name;
  std::string input_file;
  std::string output_file;
  read_args(argc, argv, program_name, input_file, output_file);
  Huffman Compression;
  std::ifstream ifs(input_file, std::ios::in | std::ios::binary);
  std::ofstream ofs(output_file,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  Compression.Compress(ifs, ofs);
  std::cout << "Compressed input file " << argv[1] << " into zap file "
            << argv[2] << '\n';
  ifs.close();
  ofs.close();
}
