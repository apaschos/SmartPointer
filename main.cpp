#include <iostream>

#include "SmartPointer.hpp"


template <typename T>
void printSPValue(SharedPointer<T> sp)
{
	if(sp)
	{
		std::cout << "printSPValue: " << *sp << std::endl;
	}
	else
	{
		std::cout << "printSPValue: nullptr" << std::endl;
	}
}

int main()
{
	SharedPointer<int> sp(new int(5));
	SharedPointer<int> sp2(std::move(sp));
	{
		SharedPointer<int> sp3(std::move(sp));
		printSPValue<int>(sp3);
	}

	printSPValue<int>(sp);
	printSPValue<int>(sp2);

	std::cout << "main: " << *sp2 << std::endl;

	return 0;
}
