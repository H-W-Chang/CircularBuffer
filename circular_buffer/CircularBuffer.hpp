#pragma once
#include <deque>
#include <mutex>
#include <array>
#include <atomic>
#include <exception>
#include <stdexcept>
#include <inttypes.h>
#include <iostream>

template <typename T, int Size>
class CircularBuffer
{
private:
	std::atomic<uint32_t> start;
	std::atomic<uint32_t> element_size;
	std::array<T, Size> buffer;
	std::mutex mutex;
public:
	explicit CircularBuffer() :start(0), element_size(0) {};
	CircularBuffer(const CircularBuffer &rhs) : start(rhs.start.load()), 
		element_size(rhs.element_size.load()), 
		buffer(rhs.buffer) {};
	CircularBuffer(CircularBuffer &&rhs) : start(rhs.start.load()), 
		element_size(rhs.element_size.load()),
		buffer(std::move(rhs.buffer)) 
	{
		rhs.start.store(0);
		rhs.element_size.store(0);
	};
	~CircularBuffer() {};
	CircularBuffer & operator = (const CircularBuffer &rhs) {
		if (this != &rhs) {
			start = rhs.start.load();			
			element_size = rhs.element_size.load();
			buffer = rhs.buffer;
			return *this;
		}
	};
	CircularBuffer & operator = (CircularBuffer &&rhs) {		
		if (this != &rhs) {
			//start = rhs.start.load();
			start = rhs.start.load();
			rhs.start.store(0);
			element_size = rhs.element_size.load();
			rhs.element_size.store(0);
			buffer = std::move(rhs.buffer);
		}
		return *this;
	};

	void push_back(const T &c);
	template <class... Args>
	void emplace_back(Args... args);
	T & front();
	void pop_front();
	T & get_and_pop();
	bool empty();
	uint32_t size();
	uint32_t max_size();
	void clear();
};

template <typename T, int Size>
void CircularBuffer<T, Size>::push_back(const T &c) {
	buffer[(start + element_size) % Size] = c;
	if ((element_size % Size) == 0) {
		if (element_size == 0) {
			element_size++;
		}
		else
		{
			start = (start + 1) % Size;
		}
	}
	else {
		element_size++;
	}
}


template <typename T, int Size>
template <class... Args>
void CircularBuffer<T, Size>::emplace_back(Args... args) {
	T t(args...);
	push_back(t);
}

template <typename T, int Size>
T & CircularBuffer<T, Size>::front() {
	if (element_size > 0) {
		return buffer[start];
	}
	else
	{
		throw std::range_error("CircularBuffer is empty");
	}
}

template <typename T, int Size>
void CircularBuffer<T, Size>::pop_front() {
	if (element_size > 0) {
		start = (start + 1) % Size;
		element_size--;
	}
	else
	{
		throw std::range_error("CircularBuffer is empty");
	}
}

template <typename T, int Size>
T & CircularBuffer<T, Size>::get_and_pop() {
	if (element_size > 0) {
		int tmp = start;
		start = (start + 1) % Size;
		element_size--;
		return buffer[tmp];
	}
	else
	{
		throw std::range_error("CircularBuffer is empty");
	}
}

template <typename T, int Size>
bool CircularBuffer<T, Size>::empty() {
	return element_size == 0;
}

template <typename T, int Size>
uint32_t CircularBuffer<T, Size>::size() {
	return element_size;
}

template <typename T, int Size>
uint32_t CircularBuffer<T, Size>::max_size() {
	return Size;
}

template <typename T, int Size>
void CircularBuffer<T, Size>::clear() {
	element_size = 0;
	start = 0;
}