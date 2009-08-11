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
		std::cout << "usage " << argv[0] << " [-s] [-S] [-c] [-rREGEXP] [-tN] file_1 .. file_n\n\n"
			"\t-s\t\tTransforma qualquer numero de brancos em um espaço, \"A    B\" fica igual a \"A B\"\n"
			"\t-S\t\tIgnora os brancos completamente, \"A B\" fica igual a \"AB\"\n"
			"\t-c\t\tIgnora comentários de uma linha do C++.\n"
			"\t-rREGEXP\tIgnora qualque match da REGEXP (perl compatible) que for encontrado.\n"
			"\t-tn\t\tIgnora blocos de copy and paste menores que n linhas.\n\n"
			"\tAs opções são processadas na ordem dada na linha de comando, ou seja \"/ / AB\" fircará igual a \"//AB\" se o usuário usar \"-c -S\" mas será completamente ignorado quando for usado \"-S -c\".\n";
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
