#include "shared_ptr.h"

int main() {
	shsred_pointer<int> ptr;
	shsred_pointer<int>ptr1(new int(5));
	shsred_pointer<int>ptr2 = ptr1;
	shsred_pointer<int>ptr3;
	ptr3 = ptr1;
	shsred_pointer<int>ptr4 = std::move(ptr1);
	std::cout << "ptr1.get_count = " << ptr1.get_count() << std::endl;
	ptr2.reset();
	return 0;
}