#include "pch.h"
#include <iostream>
#include "../circular_buffer/CircularBuffer.hpp"
using namespace std;

class MyClass {
public:
	int num;
	char ch;
	MyClass() {};
	MyClass(int _num, char _ch) :num(_num), ch(_ch) {};
};

TEST(CircularBufferTest, CopyConstructor) {
	CircularBuffer<int, 4> cb1;
	cb1.push_back(100);
	CircularBuffer<int, 4> cb2 = cb1;
	EXPECT_EQ(cb2.front(), cb1.front());
	EXPECT_EQ(cb2.size(), cb1.size());
}

TEST(CircularBufferTest, CopyAssignment) {
	CircularBuffer<int, 4> cb1;
	cb1.push_back(100);
	CircularBuffer<int, 4> cb2;
	cb2 = cb1;
	EXPECT_EQ(cb2.front(), cb1.front());
	EXPECT_EQ(cb2.size(), cb1.size());
}

TEST(CircularBufferTest, MoveConstructor) {
	CircularBuffer<int, 4> cb1;
	cb1.push_back(100);
	int a = cb1.front();
	CircularBuffer<int, 4> cb2 = std::move(cb1);
	EXPECT_EQ(cb2.front(), a);
	EXPECT_ANY_THROW(cb1.front());
	EXPECT_NE(cb2.size(), cb1.size());
}

TEST(CircularBufferTest, MoveAssignment) {
	CircularBuffer<int, 4> cb1;
	cb1.push_back(100);
	int a = cb1.front();
	CircularBuffer<int, 4> cb2;
	cb2 = std::move(cb1);
	EXPECT_EQ(cb2.front(), a);
	EXPECT_ANY_THROW(cb1.front());
	EXPECT_NE(cb2.size(), cb1.size());
}

TEST(CircularBufferTest, Push) {
	CircularBuffer<char, 4> cb;
	cb.push_back('a');
	ASSERT_TRUE(cb.size(), 1);
	cb.push_back('b');
	cb.push_back('c');
	cb.push_back('d');
	cb.push_back('e');
	ASSERT_TRUE(cb.size(), 4);
}

TEST(CircularBufferTest, ContinuousPush) {
	CircularBuffer<int, 4> cb;
	for (int i = 0; i < 1000; ++i) {
		cb.push_back(i);
	}
	EXPECT_EQ(cb.get_and_pop(), 996);
	EXPECT_EQ(cb.get_and_pop(), 997);
	EXPECT_EQ(cb.get_and_pop(), 998);
	EXPECT_EQ(cb.get_and_pop(), 999);
}

TEST(CircularBufferTest, Front) {
	CircularBuffer<char, 4> cb;
	EXPECT_ANY_THROW(cb.front());
	cb.push_back('a');
	EXPECT_EQ(cb.front(), 'a');
}


TEST(CircularBufferTest, PopFront) {
	CircularBuffer<int, 4> cb;
	EXPECT_ANY_THROW(cb.pop_front());
	cb.push_back(1);
	cb.pop_front();
	EXPECT_TRUE(cb.empty());
	EXPECT_EQ(cb.size(), 0);
}
TEST(CircularBufferTest, GetAndPop) {
	CircularBuffer<int, 4> cb;
	EXPECT_ANY_THROW(cb.get_and_pop());
	cb.push_back(1);
	int a = cb.get_and_pop();
	EXPECT_TRUE(cb.empty());
	EXPECT_EQ(cb.size(), 0);
	EXPECT_EQ(a, 1);
}

TEST(CircularBufferTest, EmplaceBack) {
	CircularBuffer<MyClass, 4> cb;
	cb.emplace_back(1, 'a');
	EXPECT_EQ(cb.front().num, 1);
	EXPECT_EQ(cb.front().ch, 'a');
	EXPECT_EQ(cb.size(), 1);
	cb.emplace_back(2, 'b');
	cb.emplace_back(3, 'c');
	cb.emplace_back(4, 'd');
	cb.emplace_back(5, 'e');
	EXPECT_EQ(cb.front().num, 2);
	EXPECT_EQ(cb.front().ch, 'b');

}

TEST(CircularBufferTest, Empty) {
	CircularBuffer<int, 4> cb;
	EXPECT_TRUE(cb.empty());
	cb.push_back(10);
	EXPECT_FALSE(cb.empty());
}

TEST(CircularBufferTest, MaxSize) {
	CircularBuffer<int, 4> cb;
	EXPECT_EQ(cb.max_size(), 4);
}

TEST(CircularBufferTest, Clear) {
	CircularBuffer<int, 4> cb;
	for (int i = 0; i < 10; i++) {
		cb.push_back(i);
	}
	cb.clear();
	EXPECT_TRUE(cb.empty());
	EXPECT_EQ(cb.size(), 0);
}