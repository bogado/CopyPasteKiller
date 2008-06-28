#include "hash.h"
#include "filedb.h"

#include <iostream>

int main()
{
	analisys::FileDB fdb;
	fdb.addFile("test.cpp");
	fdb.addFile("line.cpp");
	fdb.addFile("line.h");

	for (int i = 0; i < fdb.size(); i++)
	{
		std::cout << "\nFile: " << fdb[i] << "\n\n";

		for (int j = 0; j < fdb[i].size(); j++)
			std::cout << fdb[i][j] << " |" << fdb[i][j].content() <<  "|" << fdb[i][j].key() << "\n";
	}
}
