#ifndef BSTREAM_H_
#define BSTREAM_H_

#include <cstddef>
#include <fstream>
#include <iostream>

class BinaryInputStream {
 public:
  explicit BinaryInputStream(std::ifstream &ifs);

  bool GetBit();
  char GetChar();
  int GetInt();

 private:
  std::ifstream &ifs;
  char buffer = 0;
  size_t avail = 0;

  // Helpers
  void RefillBuffer();
};

BinaryInputStream::BinaryInputStream(std::ifstream &ifs) : ifs(ifs) {}

void BinaryInputStream::RefillBuffer() {
  // Read the next byte from the input stream
  ifs.get(buffer);
  if (ifs.gcount() != 1)
    throw std::underflow_error("No more characters to read");
  avail = 8;
}

bool BinaryInputStream::GetBit() {
  bool bit;

  if (!avail) RefillBuffer();

  avail--;
  bit = ((buffer >> avail) & 1) == 1;

#if 0  // Switch to 1 for debug purposes
  if (bit)
    std::cout << '1' << std::endl;
  else
    std::cout << '0' << std::endl;
#endif

  return bit;
}

char BinaryInputStream::GetChar() {
  char character = 0;
  for (size_t i = 0; i < 8; ++i) {
    character <<= 1;
    if (GetBit()) character |= 1;
  }
  return character;
}

int BinaryInputStream::GetInt() {
  int integer = 0;
  size_t count = sizeof(int) * 8;
  for (size_t i = 0; i < count; ++i) {
    integer <<= 1;
    if (GetBit()) integer |= 1;
  }
  return integer;
}

class BinaryOutputStream {
 public:
  explicit BinaryOutputStream(std::ofstream &ofs);
  ~BinaryOutputStream();

  void Close();

  void PutBit(bool bit);
  void PutChar(char byte);
  void PutInt(int word);

 private:
  std::ofstream &ofs;
  char buffer = 0;
  size_t count = 0;

  // Helpers
  void FlushBuffer();
};

BinaryOutputStream::BinaryOutputStream(std::ofstream &ofs) : ofs(ofs) {}

BinaryOutputStream::~BinaryOutputStream() { Close(); }

void BinaryOutputStream::Close() { FlushBuffer(); }

void BinaryOutputStream::FlushBuffer() {
  // Nothing to flush
  if (!count) return;

  // If buffer isn't complete, pad with 0s before writing
  if (count > 0) buffer <<= (8 - count);

  // Write to output stream
  ofs.put(buffer);

  // Reset buffer
  buffer = 0;
  count = 0;
}

void BinaryOutputStream::PutBit(bool bit) {
  // Make some space and add bit to buffer
  buffer <<= 1;
  if (bit) buffer |= 1;

  // If buffer is full, write it
  if (++count == 8) FlushBuffer();
}

void BinaryOutputStream::PutChar(char byte) {
  bool bit;
  for (int i = 7; i >= 0; i--) {
    bit = ((byte >> i) & 1) == 1;
    PutBit(bit);
  }
}

void BinaryOutputStream::PutInt(int word) {
  bool bit;
  size_t count = sizeof(word) * 8;
  for (int i = count - 1; i >= 0; i--) {
    bit = ((word >> i) & 1) == 1;
    PutBit(bit);
  }
}

#endif  // BSTREAM_H_
