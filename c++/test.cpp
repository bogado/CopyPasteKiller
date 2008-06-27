#include "hash.h"

#include <iostream>

int main()
{
	analisys::MD5Hasher teste;

	std::cout << "out = " << teste.hash("out") << "\n";
}
