#pragma once
#ifndef _UNIQUEPTR_H
#include <iostream>

template <class T>
class myUnique_ptr
{
private:
	T* res;
	myUnique_ptr(myUnique_ptr&) = delete; //copy constructor not allowed
	myUnique_ptr operator = (myUnique_ptr&) = delete; //assignment operator not allowed
public:
	myUnique_ptr(T* ptr = nullptr) {
		res = ptr;
	}
	~myUnique_ptr() {
		if (res)
			delete res;
	}

	myUnique_ptr (myUnique_ptr&& other) : res(other.res) {
		std::cout << "move constructor called. " << std::endl;
		other.res = nullptr;
	}

	//overload -> operator
	T* operator -> () {
		std::cout << " -> called" << std::endl;
		return res;
	}

	//overload * operator
	T& operator * () {
		std::cout << " * called" << std::endl;
		return *res;
	}

	T* get() {
		std::cout << "get function called" << std::endl;
		return res;
	}

};



#endif // !_UNIQUEPTR_H

