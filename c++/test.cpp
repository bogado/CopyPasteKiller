#include "filedb.h"
#include "result.h"
#include "resultSet.h"

#include <iostream>
#include <regex>
#include <string>
#include <sstream>

std::string removeSpacesHard(std::string str)
{
	std::tr1::regex remove("\\s+");
	return std::tr1::regex_replace(str, remove, "");
}

std::string removeSpaces(std::string str)
{
	std::tr1::regex remove("\\s+");
	return std::tr1::regex_replace(str, remove, " ");
}

std::string removeSingleLineCppComments(std::string str)
{
	std::tr1::regex remove("//.*");
	return std::tr1::regex_replace(str, remove, "");
}

int main(int argc, const char *argv[])
{
	if (argc == 1)
	{
		std::cout << "usage " << argv[0] << " [-s] [-c] [-tN] file_1 .. file_n\n";
		return 127;
	}

	unsigned threshold = 4;
	std::list<std::string> files;

	for (int i = 1; i < argc; i++)
	{
		if (std::string("-c") == argv[i])
		{
			analisys::Simplifier::setup(removeSingleLineCppComments);
		} else if (std::string("-S") == argv[i]) 
		{
			analisys::Simplifier::setup(removeSpacesHard);
		} else if (std::string("-s") == argv[i]) 
		{
			analisys::Simplifier::setup(removeSpaces);
		} else if (std::string(argv[i]).substr(0,2) == "-t") 
		{
			std::stringstream st(std::string(argv[i]).substr(2));
			st >> threshold;
		} else
		{
			files.push_back(std::string(argv[i]));
		}
	}

	analisys::FileDB fdb(threshold);

	for (std::list<std::string>::iterator i = files.begin(); i != files.end(); ++i)
		fdb.addFile(*i);

	analisys::ResultSet results = fdb.check();

	results.simplify();

	std::cout << results << "\n";
}
