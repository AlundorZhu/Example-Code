#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <array>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "bstream.h"
#include "pqueue.h"

class HuffmanNode {
 public:
  explicit HuffmanNode(char ch, size_t freq, HuffmanNode *left = nullptr,
                       HuffmanNode *right = nullptr)
      : ch_(ch), freq_(freq), left_(left), right_(right) {}

  bool IsLeaf() {
    // Node is a leaf if it doesn't have any children
    return left_ == nullptr && right_ == nullptr;
  }

  bool operator<(const HuffmanNode &n) const {
    // In case of equality, make it deterministic based on character
    if (freq_ == n.freq_) return ch_ < n.ch_;
    // Otherwise compare frequencies
    return freq_ < n.freq_;
  }

  size_t freq() { return freq_; }
  size_t data() { return ch_; }
  HuffmanNode *left() { return left_; }
  HuffmanNode *right() { return right_; }

 private:
  char ch_;
  size_t freq_;
  HuffmanNode *left_, *right_;
};

class MinHeap {
 public:
  bool operator()(const HuffmanNode *a, const HuffmanNode *b) {
    return (*a) < (*b);
  }
};

class Huffman {
 public:
  static void Compress(std::ifstream &ifs, std::ofstream &ofs);

  static void Decompress(std::ifstream &ifs, std::ofstream &ofs);

 private:
  // Helper methods...
  static HuffmanNode *BuildHuffmanTree(std::map<char, int> &freq_table);
  static void BuildFrequencyTable(std::map<char, int> &a, std::ifstream &ifs);
  static void Print(HuffmanNode *n, int level);
  static void output_tree(HuffmanNode *n, BinaryOutputStream &output);
  // caller function
  static void BuildCodeTable(HuffmanNode *n,
                             std::map<char, std::string> &coding_table);
  // recursive function
  static void BuildCodeTable(HuffmanNode *n, std::string bit_for_char,
                             std::map<char, std::string> &coding_table);
  static void Conversion(std::map<char, std::string> &coding_table,
                         std::ifstream &ifs, BinaryOutputStream &output);
  static HuffmanNode *RecreateTree(BinaryInputStream &input);
  static char GetCharacter(HuffmanNode *n, BinaryInputStream &input);
  static void Clean_up(HuffmanNode *n);
  static void PutBinaryString(std::string &str, BinaryOutputStream &output);
};

//  compression
void Huffman::Compress(std::ifstream &ifs, std::ofstream &ofs) {
  //  we need to write to a file
  BinaryOutputStream output(ofs);

  //  push those nodes into pqueue
  //  count the frequency of nodes
  //  i would do a map for this
  //  freq table should contain every character
  //  that is in the file (char) and its frequency
  //  which should be an integer
  std::map<char, int> freq_table;
  BuildFrequencyTable(freq_table, ifs);

  //  build the huffman _tree
  HuffmanNode *root = BuildHuffmanTree(freq_table);
  output_tree(root, output);  // puts encoded huff_man
                              //  put tree structure into file

  // putting number of encoded characters into binary file
  output.PutInt(root->freq());
  //  std::cout << huffman_pqueue.Top()->freq();

  //  generate code table
  std::map<char, std::string> coding_table;
  BuildCodeTable(root, coding_table);
  //  using the code table, we will now
  //  convert the input file into a binary file into the zap file
  Conversion(coding_table, ifs, output);

  output.Close();
  Clean_up(root);
}

void Huffman::BuildCodeTable(HuffmanNode *root,
                             std::map<char, std::string> &coding_table) {
  //  code table has a character correlated with a bit string
  std::string bit_for_char = "";
  BuildCodeTable(root, bit_for_char, coding_table);
}

void Huffman::BuildFrequencyTable(std::map<char, int> &a, std::ifstream &ifs) {
  //  use go into file to find characters and
  //  find how many characters
  //  as well as their frequency
  char character;
  while (ifs.get(character)) {
    if (a.find(character) == a.end()) {
      //  new character
      a.emplace(character, 1);
    } else {
      //  the character already exist
      //  make frequency of the character go up
      a[character]++;
    }
  }
}

HuffmanNode *Huffman::BuildHuffmanTree(std::map<char, int> &freq_table) {
  //  creates a min prioriy queue that takes in huffman nodes
  PQueue<HuffmanNode *, MinHeap> huffman_pqueue;
  // push frequency table as nodes into huffman_pqueue
  for (auto it = freq_table.begin(); it != freq_table.end(); it++) {
    huffman_pqueue.Push(
        new HuffmanNode(it->first, it->second, nullptr, nullptr));
  }
  /*
  From this priority queue, we then apply the following algorithm:
  Pop the top node, as node #1
  Pop the top node, as node #2
  Create a Huffman internal node, with node #1 as left child, and node #2 as
  right child The frequency for this node is the sum of both children nodes’
  frequency
  */
  while (huffman_pqueue.Size() != 1) {
    // while loop gurantees that there is a root
    HuffmanNode *node_one = huffman_pqueue.Top();  //  left child
    huffman_pqueue.Pop();
    HuffmanNode *node_two = huffman_pqueue.Top();  //  right child
    huffman_pqueue.Pop();
    //  internal node should have '0' as their character and
    //  have the frequencies of their children
    HuffmanNode *internal_node = new HuffmanNode(
        0, node_one->freq() + node_two->freq(), node_one, node_two);
    huffman_pqueue.Push(internal_node);
    //  do this until we have only one tree
  }

  return huffman_pqueue.Top();
}

void Huffman::output_tree(HuffmanNode *n, BinaryOutputStream &output) {
  //  if the node is a leaf node, put down a 1
  //  and then it's character
  if (n->IsLeaf()) {
    // std::cout << "1" << n->data();
    output.PutBit(1);
    output.PutChar(n->data());
  } else {
    //  if the node is an internal node
    //  put down a 0 and only 0
    //  std::cout << "0" << n->data();
    output.PutBit(0);
    //  preordertraverse the left side
    //  and do this until we construct
    //  entire tree
    output_tree(n->left(), output);
    output_tree(n->right(), output);
  }
}

void Huffman::BuildCodeTable(HuffmanNode *n, std::string bit_for_char,
                             std::map<char, std::string> &coding_table) {
  //  if its a leaf node then put it in the
  //  if we access code_table['A'] = 1? and its a leaf node
  //  we start at root node
  //  for every traversal downward left we gotta make it 0
  //  for every traversal downward right we make the string corresponding
  if (n->IsLeaf()) {
    coding_table.emplace(n->data(), bit_for_char);
  } else {
    //  from the code table, we know that if we go right
    //  the corresponding bit should be 1 as A is 1
    BuildCodeTable(n->right(), bit_for_char + '1', coding_table);
    //  from the diagram, we know that if we go left we add 0 to the bit string
    //  and if we go left again we hit C, which is a leaf node
    //  so then emplace the char C, and its bit_for_char which is 00 since
    //  they had to go down left twice
    //  and if we go right from that node we hit B so B in the coding table is
    //  01
    BuildCodeTable(n->left(), bit_for_char + '0', coding_table);
  }
  // for all contents in the binary file
  // replace it with either 1 or 0 or something
  // for every correspdonging character
}

void Huffman::Conversion(std::map<char, std::string> &coding_table,
                         std::ifstream &ifs, BinaryOutputStream &output) {
  //  for every bit thats in the codetable
  //  use all_ABC.txt as an example
  char character;
  //  reset the ifstream
  ifs.clear();
  //  go to the beginning of the input file
  ifs.seekg(0, std::ios::beg);
  //  do similar thing which is freq table
  //  and instead of counting everytime we hit a character
  //  and increase its character, we use our code table
  //  to then put a bit depending on the code table
  while (ifs.get(character)) {
    auto it = coding_table.find(character);
    // just to be extra careful
    if (it != coding_table.end()) {
      // if the character is in the code_table
      PutBinaryString(it->second, output);
    }
  }
}

void Huffman::PutBinaryString(std::string &str, BinaryOutputStream &output) {
  for (auto c : str) {
    //  for the length of the bit_for_char correspdoning
    //  to that character so A would be like 1 length
    //  and B / C would be 2 lengths
    //  and you iterate through the entire bit_for_char
    // and put down whether its 1 or 0 at that moment
    if (c == '1')
      output.PutBit(1);
    // be explicit to not put anything extra
    else if (c == '0')
      output.PutBit(0);
  }
}

void Huffman::Decompress(std::ifstream &ifs, std::ofstream &ofs) {
  // takes in a compressed zap file
  BinaryInputStream input(ifs);
  // will eventually output a decompressed zap file
  BinaryOutputStream output(ofs);
  // create the root node
  HuffmanNode *top;
  //  test case for when root node is present
  //  which implies huffman tree is needed
  if (!input.GetBit())
    //  if first bit is 0, implies root node with two children are there
    //  calls recursive function recreate tree
    top = new HuffmanNode('0', 0, RecreateTree(input), RecreateTree(input));
  else
    //  test case for one character which is just
    //  one node
    top = new HuffmanNode(input.GetChar(), 0, nullptr, nullptr);
  //  grabs the input of the frequency of the characters
  //  from the second part of the huffman
  int num_encoded = input.GetInt();
  //  for the amount of characters that are in the
  //  file we will get the character of the 101010 thingy mabobby
  for (int i = 0; i < num_encoded; i++) {
    ofs << GetCharacter(top, input);
  }
  Clean_up(top);
}

void Huffman::Clean_up(HuffmanNode *n) {
  if (n->left() && n->right()) {
    // Internal node
    Clean_up(n->right());
    Clean_up(n->left());
    // delete the interal node
    delete n;
    n = nullptr;
  } else if (n->left() && !n->right()) {
    // only have left child
    Clean_up(n->left());
    delete n;
    n = nullptr;
  } else if (n->right() && !n->left()) {
    // only have right child
    Clean_up(n->right());
    delete n;
    n = nullptr;
  } else {
    // Leaf node
    delete n;
    n = nullptr;
  }
}

HuffmanNode *Huffman::RecreateTree(BinaryInputStream &input) {
  //  in the structure of how we created the tree
  //  if we hit a character we put down a 1 so
  //  we check the input is
  if (input.GetBit()) {
    return new HuffmanNode(input.GetChar(), 0, nullptr, nullptr);
  } else {
    //  in the structure of how we created the tree
    //  if we hit a character we put down a 1 so we check the input is
    return new HuffmanNode('0', 0, RecreateTree(input), RecreateTree(input));
  }
}

//  same code from how to generate coding_table
char Huffman::GetCharacter(HuffmanNode *n, BinaryInputStream &input) {
  //  the only time you will ever return a char is when the node is a
  //  leaf node
  if (n->IsLeaf()) {
    return n->data();
  }
  if (input.GetBit()) {
    //  in coding_table, when you put down a 1, you go
    //  go right
    return GetCharacter(n->right(), input);
  } else {
    //  in coding_table, when you put down a 0, you go
    // go left
    return GetCharacter(n->left(), input);
  }
}

#endif  // HUFFMAN_H_
