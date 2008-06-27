#include "hash.h"
#include "file.h"

#include <iostream>

int main()
{
	analisys::File f("test.cpp");

	for (int i = 0; i < f.size(); i++)
		std::cout << f[i] << " |" << f[i].content() <<  "|" << f[i].key() << "\n";
}
