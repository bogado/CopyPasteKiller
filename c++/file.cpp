#include "file.h"
#include "line.h"

namespace analisys {

void File::init(Ptr filePtr)
{
	std::fstream file(filename_.c_str(), std::fstream::in);

	unsigned int n = 0;
	std::string l;
	while ( !file.eof() )
	{
		std::getline(file, l);
		if (!file.eof())
			lines_.push_back(Line(filePtr, n, l));
		n++;
	}

	file.close();
}

}
