#include "filedb.h"
#include "result.h"
#include "resultSet.h"

#include <iostream>
#include <regex>
#include <string>
#include <sstream>

class RegexpReplacer
{
public:
	RegexpReplacer(std::string regexp, std::string replace) : remove_(regexp), replace_(replace)
	{}

	std::string operator  ()(std::string str)
	{
		return regex_replace(str, remove_, replace_);
	}

private:
	std::tr1::regex remove_;
	std::string replace_;
};

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
		std::string arg(argv[i]);
		if (std::string("-c") == arg)
		{
			analisys::Simplifier::setup(RegexpReplacer("//.*", ""));
		} else if (std::string("-S") == arg) 
		{
			analisys::Simplifier::setup(RegexpReplacer("\\s+", ""));
		} else if (std::string("-s") == arg) 
		{
			analisys::Simplifier::setup(RegexpReplacer("\\s+", " "));
		} else if (arg.substr(0,2) == "-r")
		{
			analisys::Simplifier::setup(RegexpReplacer(arg.substr(2), ""));
		} else if (arg.substr(0,2) == "-t") 
		{
			std::stringstream st(arg.substr(2));
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
