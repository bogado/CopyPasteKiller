#include "hash.h"
#include "filedb.h"
#include "result.h"

#include <iostream>

int main()
{
	analisys::FileDB fdb;
	fdb.addFile("../teste1");
	fdb.addFile("../teste2");

	std::cout << fdb.check() << "\n";
}
