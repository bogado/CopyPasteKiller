#include "file.h"

namespace analisys {

File::File(std::string filename) : filename_(filename)
{
	struct stat st;
	if (stat(filename.c_str(), &st) || !S_ISREG(st.st_mode))
		throw NoSuchFile(filename);
}

File::Ptr File::build(std::string filename, const Simplifier& simp)
{
	Ptr file = Ptr(new File(filename));

	file->init(file, simp);

	return file;
}

void File::init(Ptr filePtr, const Simplifier& simp)
{
	std::fstream file(filename_.c_str(), std::fstream::in);

	unsigned int n = 0;
	std::string l;
	while (!file.eof())
	{
		std::getline(file, l);
		if (!file.eof())
		{
			lines_.push_back(Line(filePtr, n, l, simp));
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

File::Line &File::operator [](unsigned n)
{
	if (n >= lines_.size())
		throw(NoSuchLine(filename_));

	return lines_[n];
}

unsigned int File::size() const
{
	return lines_.size();
}

bool File::Line::valid(unsigned n) const
{
	if (n + num_ < file()->size())
		return true;

	return false;
}

}
