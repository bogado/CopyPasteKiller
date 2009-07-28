#include "filedb.h"
#include "result.h"
#include "resultSet.h"

#include <iostream>
#include <regex>
#include <string>

std::string removeSpaces(const std::string& str)
{
	static std::tr1::regex remove("\\s+");
	return std::tr1::regex_replace(str, remove, " ");
}

int main(int argc, const char *argv[])
{
	if (argc == 1)
	{
		std::cout << "usage " << argv[0] << " file_1 .. file_n\n";
		return 127;
	}

	analisys::Simplifier::setup(removeSpaces);
	analisys::FileDB fdb;

	for (int i = 1; i < argc; i++)
		fdb.addFile(argv[i]);

	analisys::ResultSet results = fdb.check();

	results.simplify();

	std::cout << results << "\n";
}
