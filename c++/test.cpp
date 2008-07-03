#include "hash.h"
#include "filedb.h"
#include "result.h"

#include <iostream>

int main()
{
	analisys::FileDB fdb;
	fdb.addFile("test.cpp");
	fdb.addFile("line.cpp");
	fdb.addFile("line.h");

	std::cout << fdb.check() << "\n";
}
