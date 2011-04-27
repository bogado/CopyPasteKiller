#include "filedb.h"
#include "result.h"
#include "resultSet.h"

#include <iostream>
#include <string>
#include <sstream>

#include "boost/regex.hpp"

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
	boost::regex remove_;
	std::string replace_;
};

int main(int argc, const char *argv[])
{
	if (argc == 1)
	{
		std::cout << "usage " << argv[0] << " [-s] [-S] [-c] [-rREGEXP] [-tN] [-v] file_1 .. file_n\n\n"
			"\t-s\t\tTransforma qualquer numero de brancos em um espaço, \"A    B\" fica igual a \"A B\"\n"
			"\t-S\t\tIgnora os brancos completamente, \"A B\" fica igual a \"AB\"\n"
			"\t-c\t\tIgnora comentários de uma linha do C++.\n"
			"\t-rREGEXP\tIgnora qualque match da REGEXP (perl compatible) que for encontrado.\n"
			"\t-tn\t\tIgnora blocos de copy and paste menores que n linhas.\n"
			"\t-v\t\tVerbose, mostra o bloco copiado encontrado.\n"
			"\tAs opções são processadas na ordem dada na linha de comando, ou seja \"/ / AB\" fircará igual a \"//AB\" se o usuário usar \"-c -S\" mas será completamente ignorado quando for usado \"-S -c\".\n";
		return 127;
	}

	bool verbose = false;
	unsigned threshold = 4;
	std::list<std::string> files;
	analisys::Simplifier simp;

	for (int i = 1; i < argc; i++)
	{
		std::string arg(argv[i]);
		if ("-c" == arg)
		{
			simp.add(RegexpReplacer("//.*", ""));
		} else if ("-S" == arg) 
		{
			simp.add(RegexpReplacer("\\s+", ""));
		} else if ("-s" == arg) 
		{
			simp.add(RegexpReplacer("\\s+", " "));
		} else if ("-v" == arg)
		{
			verbose = true;
		} else if (arg.substr(0,2) == "-r")
		{
			simp.add(RegexpReplacer(arg.substr(2), ""));
		} else if (arg.substr(0,2) == "-t") 
		{
			std::stringstream st(arg.substr(2));
			st >> threshold;
		} else
		{
			files.push_back(std::string(argv[i]));
		}
	}

	analisys::FileDB fdb(threshold, simp);

	for (std::list<std::string>::iterator i = files.begin(); i != files.end(); ++i)
		fdb.addFile(*i);

	analisys::ResultSet results = fdb.check();

	results.simplify();
	results.setVerbose(verbose);

	std::cout << results << "\n";
}
