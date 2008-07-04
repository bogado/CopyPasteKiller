#include "file.h"
#include "line.h"

namespace analisys {

FileImpl::FileImpl(std::string filename) : filename_(filename)
{
	std::fstream file(filename.c_str(), std::fstream::in);

	unsigned int n = 0;
	std::string l;
	while ( !file.eof() )
	{
		n++;
		std::getline(file, l);
		if (!file.eof())
			lines_.push_back(Line(this, n, l));
	}

	file.close();
}

}
