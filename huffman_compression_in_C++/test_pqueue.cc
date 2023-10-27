#include <gtest/gtest.h>

#include <functional>

#include "pqueue.h"

TEST(PQueue, less) {
  PQueue<int> pq;

  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 2);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 23);
}

TEST(PQueue, randomInsertionsSimpleSearch) {
  PQueue<int> pq;
  for (int i = 0; i < 10; i++) {
    pq.Push(i * i);
  }
  EXPECT_EQ(pq.Top(), 0);
  EXPECT_EQ(pq.Size(), 10);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 1);
}

TEST(PQueue, randomInsertionsGreaterSearchEverything) {
  PQueue<int> pq;
  for (int i = 0; i < 10; i++) {
    pq.Push(i * i);
  }
  EXPECT_EQ(pq.Top(), 0);
  EXPECT_EQ(pq.Size(), 10);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 1);
  EXPECT_EQ(pq.Size(), 9);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 4);
  EXPECT_EQ(pq.Size(), 8);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 9);
  EXPECT_EQ(pq.Size(), 7);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 16);
  EXPECT_EQ(pq.Size(), 6);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 25);
  EXPECT_EQ(pq.Size(), 5);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 36);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 49);
  EXPECT_EQ(pq.Size(), 3);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 64);
  EXPECT_EQ(pq.Size(), 2);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 81);
  EXPECT_EQ(pq.Size(), 1);
  pq.Pop();
  EXPECT_THROW(pq.Top(), std::exception);
}

TEST(PQueue, randomInsertionsThenRemoveAll) {
  PQueue<int> pq;
  for (int i = 1; i < 10; i++) {
    pq.Push(i * i);
  }
  for (int i = 1; i < 10; i++) {
    pq.Pop();
  }
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
}

TEST(PQueue, great) {
  PQueue<int, std::greater<int>> pq;

  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 42);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 34);
}

TEST(PQueue, randomInsertionsLessSearchEverything) {
  PQueue<int> pq;
  for (int i = 0; i < 10; i++) {
    pq.Push(i * i);
  }
  EXPECT_EQ(pq.Top(), 0);
  EXPECT_EQ(pq.Size(), 10);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 1);
  EXPECT_EQ(pq.Size(), 9);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 4);
  EXPECT_EQ(pq.Size(), 8);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 9);
  EXPECT_EQ(pq.Size(), 7);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 16);
  EXPECT_EQ(pq.Size(), 6);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 25);
  EXPECT_EQ(pq.Size(), 5);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 36);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 49);
  EXPECT_EQ(pq.Size(), 3);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 64);
  EXPECT_EQ(pq.Size(), 2);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 81);
  EXPECT_EQ(pq.Size(), 1);
  pq.Pop();
  EXPECT_THROW(pq.Top(), std::exception);
}

TEST(PQueue, randomInsertionsGreater) {
  PQueue<int, std::greater<int>> pq;
  for (int i = 0; i < 10; i++) {
    pq.Push(i * i);
  }
  EXPECT_EQ(pq.Top(), 81);
  EXPECT_EQ(pq.Size(), 10);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 64);
}

TEST(PQueue, randomInsertionsThenRemoveAllGreater) {
  PQueue<int, std::greater<int>> pq;
  for (int i = 1; i < 10; i++) {
    pq.Push(i * i);
  }
  for (int i = 1; i < 10; i++) {
    pq.Pop();
  }
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
}

TEST(PQueue, emptyForGreater) {
  PQueue<int, std::greater<int>> pq;
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
  EXPECT_THROW(pq.Pop(), std::exception);
}

TEST(PQueue, emptyForLess) {
  PQueue<int, std::greater<int>> pq;
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
  EXPECT_THROW(pq.Pop(), std::exception);
}

TEST(PQueue, lessDouble) {
  PQueue<double> pq;

  pq.Push(42.3);
  pq.Push(23.1);
  pq.Push(3.1415);
  pq.Push(34.323);

  EXPECT_EQ(pq.Top(), 3.1415);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 23.1);
}

TEST(PQueue, lessDoubleException) {
  PQueue<double> pq;
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
  EXPECT_THROW(pq.Pop(), std::exception);
}

TEST(PQueue, greatDouble) {
  PQueue<double, std::greater<double>> pq;

  pq.Push(42.3);
  pq.Push(23.1);
  pq.Push(3.1415);
  pq.Push(34.323);

  EXPECT_EQ(pq.Top(), 42.3);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 34.323);
}

TEST(PQueue, greatDoubleException) {
  PQueue<double, std::greater<double>> pq;
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
  EXPECT_THROW(pq.Pop(), std::exception);
}

class MyClass {
 public:
  explicit MyClass(int n) : n_(n) {}
  bool operator<(const MyClass& mc) const { return n_ < mc.n_; }
  int n() { return n_; }

 private:
  int n_;
};

TEST(PQueue, custom_class) {
  std::vector<MyClass> vec{MyClass(42), MyClass(23), MyClass(2), MyClass(34)};

  PQueue<MyClass> pq;
  pq.Push(vec[0]);
  pq.Push(vec[1]);
  pq.Push(vec[2]);
  pq.Push(vec[3]);

  EXPECT_EQ(pq.Top().n(), vec[2].n());
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top().n(), vec[1].n());
}

TEST(PQueue, custom_class_exception) {
  std::vector<MyClass> vec{MyClass(42), MyClass(23), MyClass(2), MyClass(34)};

  PQueue<MyClass> pq;
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
  EXPECT_THROW(pq.Pop(), std::exception);
}

class MinHeap {
 public:
  bool operator()(const MyClass* a, const MyClass* b) { return (*a) < (*b); }
};

#if 1
TEST(PQueue, custom_class_pointer) {
  std::vector<MyClass*> vec{new MyClass(42), new MyClass(23), new MyClass(2),
                            new MyClass(34)};

  PQueue<MyClass*, MinHeap> pq;
  pq.Push(vec[0]);
  pq.Push(vec[1]);
  pq.Push(vec[2]);
  pq.Push(vec[3]);

  EXPECT_EQ(pq.Top(), vec[2]);  // vec[2] is min so the top
  // so this is a minpqueue lol
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), vec[1]);  // this is def a min pqueue
}
#endif

TEST(PQueue, custom_class_pointer_exception) {
  std::vector<MyClass*> vec{new MyClass(42), new MyClass(23), new MyClass(2),
                            new MyClass(34)};

  PQueue<MyClass*, MinHeap> pq;
  EXPECT_THROW(pq.Top(), std::exception);
  EXPECT_EQ(pq.Size(), 0);
  EXPECT_THROW(pq.Pop(), std::exception);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
