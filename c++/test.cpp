#include "hash.h"
#include "filedb.h"
#include "result.h"

#include <iostream>

int main()
{
#if 1
	analisys::FileDB fdb;
	fdb.addFile("../teste1");
	fdb.addFile("../teste2");

	std::cout << fdb.check() << "\n";
#else

	analisys::File f1 = analisys::File("../teste1");
	analisys::File f2 = analisys::File("../teste2");

	analisys::Result res;

	res.add(f1[15]);
	res.add(f1[22]);
	res.add(f2[18]);

	analisys::KeyChecker check(f2[18]);
	std::cout << res << "\n";
	res.grow(check);
	std::cout << res << "\n";
	res.grow(check);
	std::cout << res << "\n";
#endif
}
