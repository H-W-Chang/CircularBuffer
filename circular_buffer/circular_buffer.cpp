// circular_buffer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <deque>
#include <assert.h>
#include "CircularBuffer.hpp"
using namespace std;

class MyClass {
public:
	int num;
	char ch;
	MyClass() {};
	MyClass(int _num, char _ch) :num(_num), ch(_ch) {};
};

int main()
{
	cout << "__cplusplus " << __cplusplus << endl;
	cout << "_MSC_VER " << _MSC_VER << endl;
	cout << "_MSVC_LANG " << _MSVC_LANG << endl;
	
	try {
		CircularBuffer<char, 10> circularBufferChar;
		circularBufferChar.push_back('a');
		circularBufferChar.push_back('b');
		circularBufferChar.push_back('c');
		circularBufferChar.push_back('d');
		circularBufferChar.push_back('e');
		cout << circularBufferChar.get_and_pop();
		cout << circularBufferChar.get_and_pop();
		cout << circularBufferChar.get_and_pop();
		cout << circularBufferChar.get_and_pop();
		cout << endl;
	}
	catch (exception &e) {
		cout << e.what() << endl;
	}
	try {
		CircularBuffer<MyClass, 10> circularBufferMyClass;
		cout << "circularBufferMyClass max size " << circularBufferMyClass.max_size() << endl;
		circularBufferMyClass.emplace_back(1, 'a');
		circularBufferMyClass.emplace_back(2, 'b');
		circularBufferMyClass.emplace_back(3, 'c');
		cout << "circularBufferMyClass current size " << circularBufferMyClass.size() << endl;
		cout << circularBufferMyClass.front().num << " ";
		cout << circularBufferMyClass.get_and_pop().ch << endl;
		cout << circularBufferMyClass.front().num << " ";
		cout << circularBufferMyClass.get_and_pop().ch << endl;
		cout << circularBufferMyClass.front().num << " ";
		cout << circularBufferMyClass.get_and_pop().ch << endl;

		circularBufferMyClass.clear();
		cout << circularBufferMyClass.front().num << " ";
	}
	catch (exception &e) {
		cout << e.what() << endl;
	}
		
	return 0;
}