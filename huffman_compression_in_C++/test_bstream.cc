#include <gtest/gtest.h>

#include <cassert>
#include <cstdio>
#include <fstream>

#include "bstream.h"

TEST(BStream, input) {
  std::string filename{"test_bstream_input"};

  const unsigned char val[] = {
      0x58, 0x90, 0xab, 0x08, 0x00, 0x4e, 0xdb, 0x40,
  };
  // Equivalent in binary is:
  // 0101100010010000101010110000100000000000010011101101101101000000
  // ^5  ^8  ^9  ^0  ^a  ^b  ^0  ^8  ^0  ^0  ^4  ^e  ^d  ^b  ^4  ^0

  // Write this to a file
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  ofs.write(reinterpret_cast<const char *>(val), sizeof(val));
  ofs.close();

  // Read it back in binary format
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);

  // Make sure that we reading the binary in the correct order
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ(bis.GetBit(), 1);
  EXPECT_EQ(bis.GetChar(), 0x62);  // 01100010
  EXPECT_EQ(bis.GetChar(), 0x42);  // 01000010
  EXPECT_EQ(bis.GetBit(), 1);
  EXPECT_EQ(bis.GetInt(), 0x58400276);  // 01011000010000000000001001110110

  ifs.close();

  std::remove(filename.c_str());
}

TEST(BStream, output) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  output.PutBit(1);
  output.PutBit(0);
  output.PutChar(0x62);
  output.PutChar(0x42);
  output.PutInt(2);
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ(bis.GetBit(), 1);
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ(bis.GetChar(), 'b');  // 01100010
  EXPECT_EQ(bis.GetChar(), 'B');  // 01000010
  EXPECT_EQ(bis.GetInt(), 2);

  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, OutputBitToChar) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  // 01100010 is equal to b
  output.PutBit(0);
  output.PutBit(1);
  output.PutBit(1);
  output.PutBit(0);
  output.PutBit(0);
  output.PutBit(0);
  output.PutBit(1);
  output.PutBit(0);
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);

  BinaryInputStream bis(ifs);
  EXPECT_EQ(bis.GetChar(), 'b');

  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, OutputBits) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);

  output.PutBit(1);
  output.PutBit(0);
  output.PutBit(0);
  output.PutBit(0);
  output.PutBit(0);
  output.PutBit(0);
  output.PutBit(1);
  output.PutBit(1);
  output.PutBit(0);
  output.PutBit(1);
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);

  BinaryInputStream bis(ifs);
  EXPECT_EQ(bis.GetBit(), 1);
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ(bis.GetBit(), 1);
  EXPECT_EQ(bis.GetBit(), 1);
  EXPECT_EQ(bis.GetBit(), 0);
  EXPECT_EQ(bis.GetBit(), 1);

  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, LowerAlphabet) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  output.PutChar(0x61);
  output.PutChar(0x62);
  output.PutChar(0x63);
  output.PutChar(0x64);
  output.PutChar(0x65);
  output.PutChar(0x66);
  output.PutChar(0x67);
  output.PutChar(0x68);
  output.PutChar(0x69);
  output.PutChar(0x6A);
  output.PutChar(0x6B);
  output.PutChar(0x6C);
  output.PutChar(0x6D);
  output.PutChar(0x6E);
  output.PutChar(0x6F);
  output.PutChar(0x70);
  output.PutChar(0x71);
  output.PutChar(0x72);
  output.PutChar(0x73);
  output.PutChar(0x74);
  output.PutChar(0x75);
  output.PutChar(0x76);
  output.PutChar(0x77);
  output.PutChar(0x78);
  output.PutChar(0x79);
  output.PutChar(0x7A);
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ(bis.GetChar(), 'a');
  EXPECT_EQ(bis.GetChar(), 'b');
  EXPECT_EQ(bis.GetChar(), 'c');  //
  EXPECT_EQ(bis.GetChar(), 'd');  //
  EXPECT_EQ(bis.GetChar(), 'e');  //
  EXPECT_EQ(bis.GetChar(), 'f');  //
  EXPECT_EQ(bis.GetChar(), 'g');  //
  EXPECT_EQ(bis.GetChar(), 'h');  //
  EXPECT_EQ(bis.GetChar(), 'i');  //
  EXPECT_EQ(bis.GetChar(), 'j');  //
  EXPECT_EQ(bis.GetChar(), 'k');  //
  EXPECT_EQ(bis.GetChar(), 'l');  //
  EXPECT_EQ(bis.GetChar(), 'm');  //
  EXPECT_EQ(bis.GetChar(), 'n');  //
  EXPECT_EQ(bis.GetChar(), 'o');  //
  EXPECT_EQ(bis.GetChar(), 'p');  //
  EXPECT_EQ(bis.GetChar(), 'q');  //
  EXPECT_EQ(bis.GetChar(), 'r');  //
  EXPECT_EQ(bis.GetChar(), 's');  //
  EXPECT_EQ(bis.GetChar(), 't');  //
  EXPECT_EQ(bis.GetChar(), 'u');  //
  EXPECT_EQ(bis.GetChar(), 'v');  //
  EXPECT_EQ(bis.GetChar(), 'w');  //
  EXPECT_EQ(bis.GetChar(), 'x');  //
  EXPECT_EQ(bis.GetChar(), 'y');  //
  EXPECT_EQ(bis.GetChar(), 'z');  //
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, UpperAlphabet) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  output.PutChar(0x41);
  output.PutChar(0x42);
  output.PutChar(0x43);
  output.PutChar(0x44);
  output.PutChar(0x45);
  output.PutChar(0x46);
  output.PutChar(0x47);
  output.PutChar(0x48);
  output.PutChar(0x49);
  output.PutChar(0x4A);
  output.PutChar(0x4B);
  output.PutChar(0x4C);
  output.PutChar(0x4D);
  output.PutChar(0x4E);
  output.PutChar(0x4F);
  output.PutChar(0x50);
  output.PutChar(0x51);
  output.PutChar(0x52);
  output.PutChar(0x53);
  output.PutChar(0x54);
  output.PutChar(0x55);
  output.PutChar(0x56);
  output.PutChar(0x57);
  output.PutChar(0x58);
  output.PutChar(0x59);
  output.PutChar(0x5A);
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ(bis.GetChar(), 'A');
  EXPECT_EQ(bis.GetChar(), 'B');
  EXPECT_EQ(bis.GetChar(), 'C');
  EXPECT_EQ(bis.GetChar(), 'D');
  EXPECT_EQ(bis.GetChar(), 'E');
  EXPECT_EQ(bis.GetChar(), 'F');
  EXPECT_EQ(bis.GetChar(), 'G');
  EXPECT_EQ(bis.GetChar(), 'H');
  EXPECT_EQ(bis.GetChar(), 'I');
  EXPECT_EQ(bis.GetChar(), 'J');
  EXPECT_EQ(bis.GetChar(), 'K');
  EXPECT_EQ(bis.GetChar(), 'L');
  EXPECT_EQ(bis.GetChar(), 'M');
  EXPECT_EQ(bis.GetChar(), 'N');
  EXPECT_EQ(bis.GetChar(), 'O');
  EXPECT_EQ(bis.GetChar(), 'P');
  EXPECT_EQ(bis.GetChar(), 'Q');
  EXPECT_EQ(bis.GetChar(), 'R');
  EXPECT_EQ(bis.GetChar(), 'S');
  EXPECT_EQ(bis.GetChar(), 'T');
  EXPECT_EQ(bis.GetChar(), 'U');
  EXPECT_EQ(bis.GetChar(), 'V');
  EXPECT_EQ(bis.GetChar(), 'W');
  EXPECT_EQ(bis.GetChar(), 'X');
  EXPECT_EQ(bis.GetChar(), 'Y');
  EXPECT_EQ(bis.GetChar(), 'Z');
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, FrequencyTestForChar) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  for (int i = 0; i < 30; i++) {
    output.PutChar(0x41);
  }
  for (int i = 0; i < 20; i++) {
    output.PutChar(0x42);
  }
  for (int i = 0; i < 10; i++) {
    output.PutChar(0x43);
  }
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  for (int i = 0; i < 30; i++) {
    EXPECT_EQ(bis.GetChar(), 'A');
  }
  for (int i = 0; i < 20; i++) {
    EXPECT_EQ(bis.GetChar(), 'B');
  }
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(bis.GetChar(), 'C');
  }
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, FrequencyTestForBits) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  for (int i = 0; i < 100; i++) {
    output.PutBit(1);
  }
  for (int i = 0; i < 100; i++) {
    output.PutBit(0);
  }
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(bis.GetBit(), 1);
  }
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(bis.GetBit(), 0);
  }
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, FrequencyTestForInts) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  for (int i = 0; i < 15; i++) {
    output.PutInt(23);
  }
  for (int i = 0; i < 20; i++) {
    output.PutInt(15);
  }
  for (int i = 0; i < 30; i++) {
    output.PutInt(37);
  }
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  for (int i = 0; i < 15; i++) {
    EXPECT_EQ(bis.GetInt(), 23);
  }
  for (int i = 0; i < 20; i++) {
    EXPECT_EQ(bis.GetInt(), 15);
  }
  for (int i = 0; i < 30; i++) {
    EXPECT_EQ(bis.GetInt(), 37);
  }
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, FrequencyTestForAllDataTypes) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  for (int i = 0; i < 15; i++) {
    output.PutInt(10);
  }
  for (int i = 0; i < 20; i++) {
    output.PutChar(0x41);
  }
  for (int i = 0; i < 30; i++) {
    output.PutBit(1);
    output.PutBit(0);
  }
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  for (int i = 0; i < 15; i++) {
    EXPECT_EQ(bis.GetInt(), 10);
  }
  for (int i = 0; i < 20; i++) {
    EXPECT_EQ(bis.GetChar(), 'A');
  }
  for (int i = 0; i < 30; i++) {
    EXPECT_EQ(bis.GetBit(), 1);
    EXPECT_EQ(bis.GetBit(), 0);
  }
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, Empty) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  for (int i = 0; i < 15; i++) {
    EXPECT_THROW(bis.GetInt(), std::exception);
  }
  for (int i = 0; i < 20; i++) {
    EXPECT_THROW(bis.GetChar(), std::exception);
  }
  for (int i = 0; i < 30; i++) {
    EXPECT_THROW(bis.GetBit(), std::exception);
    EXPECT_THROW(bis.GetBit(), std::exception);
  }
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, SpecialChars) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  output.PutChar(0x21);
  output.PutChar(0x22);
  output.PutChar(0x23);
  output.PutChar(0x24);
  output.PutChar(0x25);
  output.PutChar(0x26);
  output.PutChar(0x28);
  output.PutChar(0x29);
  output.PutChar(0x2A);
  output.PutChar(0x2B);
  output.PutChar(0x2C);
  output.PutChar(0x2D);
  output.PutChar(0x2E);
  output.PutChar(0x2F);
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ(bis.GetChar(), '!');
  EXPECT_EQ(bis.GetChar(), '"');
  EXPECT_EQ(bis.GetChar(), '#');
  EXPECT_EQ(bis.GetChar(), '$');
  EXPECT_EQ(bis.GetChar(), '%');
  EXPECT_EQ(bis.GetChar(), '&');
  EXPECT_EQ(bis.GetChar(), '(');
  EXPECT_EQ(bis.GetChar(), ')');
  EXPECT_EQ(bis.GetChar(), '*');
  EXPECT_EQ(bis.GetChar(), '+');
  EXPECT_EQ(bis.GetChar(), ',');
  EXPECT_EQ(bis.GetChar(), '-');
  EXPECT_EQ(bis.GetChar(), '.');
  EXPECT_EQ(bis.GetChar(), '/');
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, Exception) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_THROW(bis.GetBit(), std::exception);
  EXPECT_THROW(bis.GetChar(), std::exception);
  EXPECT_THROW(bis.GetInt(), std::exception);
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, ExceptionOnceReachEndOfFile) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  output.PutChar(0x62);
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ(bis.GetChar(), 'b');
  EXPECT_THROW(bis.GetChar(), std::exception);
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, Whitespace) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  output.PutChar(0x20);
  output.PutChar(0x62);
  output.PutChar(0x20);
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ(bis.GetChar(), ' ');
  EXPECT_EQ(bis.GetChar(), 'b');
  EXPECT_EQ(bis.GetChar(), ' ');
  ifs.close();
  std::remove(filename.c_str());
}

TEST(BStream, Tabs) {
  std::string filename{"test_bstream_input"};
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::trunc | std::ios::binary);
  BinaryOutputStream output(ofs);
  output.PutChar(0x09);
  output.PutChar(0x62);
  output.PutChar(0x09);
  output.Close();
  ofs.close();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  BinaryInputStream bis(ifs);
  EXPECT_EQ(bis.GetChar(), '\t');
  EXPECT_EQ(bis.GetChar(), 'b');
  EXPECT_EQ(bis.GetChar(), '\t');
  ifs.close();
  std::remove(filename.c_str());
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
