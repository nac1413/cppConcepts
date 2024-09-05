#pragma once
#ifndef _SHAREDPOINTER_H_
#define _SHAREDPOINTER_H_
#include <iostream>

template<class T>
class shsred_pointer {
private:
	T* res;
	int* counter;

	void increment() {
		if (res )
			(*counter)++;
	}

	void decrement() {
		if (res) {
			if (counter)
				*counter--;
			if(*counter == 0) {
				if(res)	{
					res = nullptr;
					counter = nullptr;
					delete res;
					delete counter;
				}
			}
		}
	}

public:
	/*default or parameterise constructor*/
	shsred_pointer(T* other = nullptr) : res(other), counter(new int(1)) { 
		std::cout << "Constructor has been called" << std::endl;
	}
	~shsred_pointer() {
		std::cout << "Destructor has been called" << std::endl;
		decrement();
	}
	/*copy constructor*/
	shsred_pointer(const shsred_pointer& other) {
		res = other.res;
		counter = other.res;
		increment();
	}
	/* copy assignment operator*/
	shsred_pointer* operator = (shsred_pointer& other) {
		if (this != &other)
		{
			decrement();
			res = other.res;
			counter = other.res;
			increment();
		}
		return this;
	}

	/* move assignment operator */
	shsred_pointer& operator = (const shsred_pointer&& other) {
		this->counter = other.counter;
		this->res = other.res;

		other.res = nullptr;
		other.counter = nullptr;
	}

	/* move copy constructor operator */
	shsred_pointer (shsred_pointer&& other) {
		increment();
		counter = other.counter;
		res = other.res;

		other.res = nullptr;
		other.counter = nullptr;
	}

	/* get the value of resource one shared pointer have */
	int get_count() {
		if (counter)
			return *counter;
		else
			return -1;
	}
	/* overload -> operator */

	T* operator ->() {
		return res;
	}

	T& operator *() {
		return *res;
	}

	void reset() {
		if (res) {
			res = nullptr;
			*counter = 0;
			counter = nullptr;
		}
	}
};
#endif // !_SHAREDPOINTER_H_

