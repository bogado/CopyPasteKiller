#include "hash.h"
#include "filedb.h"
#include "result.h"
#include "resultSet.h"

#include <iostream>

int main()
{
#if 0
	analisys::FileDB fdb;
	fdb.addFile("../teste1");
	fdb.addFile("../teste2");

	analisys::ResultSet results = fdb.check();
	results.simplify();

	std::cout << results << "\n";
#else

	analisys::File f1 = analisys::File("../teste1");
	analisys::File f2 = analisys::File("../teste2");

	analisys::Result res;

	res.add(f1[27]);
	res.add(f2[23]);

	analisys::KeyChecker checker(f1[27]);
	res.grow(checker);

	std::cout << "res = " << res << "\n";

	analisys::Result res2;

	res2.add(f1[28]);
	res2.add(f2[24]);

	std::cout << "res2 = " << res2 << "\n";

	std::cout << "res2 belongs to res ? " << (res.belongs(res2) ? "yes" : "no") << "\n";
	std::cout << "res belongs to res2 ? " << (res2.belongs(res) ? "yes" : "no") << "\n";
#endif
}
