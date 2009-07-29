#include "filedb.h"
#include "result.h"
#include "resultSet.h"

#include <iostream>
#include <regex>
#include <string>

std::string removeSpaces(const std::string& str)
{
	std::tr1::regex remove("\\s+");
	return std::tr1::regex_replace(str, remove, " ");
}

std::string removeSingleLineCppComments(const std::string& str)
{
	std::tr1::regex remove("//.*");
	return std::tr1::regex_replace(str, remove, "");
}

int main(int argc, const char *argv[])
{
	if (argc == 1)
	{
		std::cout << "usage " << argv[0] << " [-s] [-c] file_1 .. file_n\n";
		return 127;
	}

	analisys::FileDB fdb;

	for (int i = 1; i < argc; i++)
	{
		std::cout << i << "\n";
		if (std::string("-c") == argv[i])
		{
			analisys::Simplifier::setup(removeSingleLineCppComments);
		} else if (std::string("-s") == argv[i]) 
		{
			analisys::Simplifier::setup(removeSpaces);
		} else
		{
			fdb.addFile(std::string(argv[i]));
		}
	}

	analisys::ResultSet results = fdb.check();

	results.simplify();

	std::cout << results << "\n";
}
