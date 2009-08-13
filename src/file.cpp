#include "file.h"
#include "line.h"

namespace analisys {

void File::init(Ptr filePtr)
{
	std::fstream file(filename_.c_str(), std::fstream::in);

	unsigned int n = 0;
	std::string l;
	while (!file.eof())
	{
		std::getline(file, l);
		if (!file.eof())
		{
			lines_.push_back(Line(filePtr, n, l));
		}
		n++;
	}

	file.close();
}

std::string File::makeKey(const Line& line, unsigned t)
{
	return makeKey(line.num(), t);
}

std::string File::makeKey(unsigned ln, unsigned t)
{
	std::string key;
	for(unsigned j = 0; j < t; j++)
	{
		if (size() < ln + j)
		{
			return key;
		}

		Line &line = lines_[ln + j];

		key += "(" + line.key() + ")";
	}

	return key;
}

}
