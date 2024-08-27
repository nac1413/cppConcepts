#include "uniquePtr.h"

int main() {
	myUnique_ptr<int> ptr = new int(5);
	myUnique_ptr<int> ptr1(std::move(ptr));
	myUnique_ptr<int> ptr2 = new int(5);
	myUnique_ptr<int> ptr3 = std::move(ptr2);
	return 0;
}