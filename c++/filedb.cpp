#include "filedb.h"

namespace analisys {

std::string FileDB::makeKey(File::Ptr file, unsigned line)
{
	std::string key;
	for(unsigned j = 0; j < threshold_; j++)
		key += "(" + (*file)[line + j].key() + ")";
	return key;
}

void FileDB::addFile(const std::string& filename)
{
	files_.push_back(File::build(filename));
	File::Ptr file = files_[files_.size() -1];

	for(unsigned i = 0; i < file->size() - threshold_; i++)
	{
		lines_.insert(make_pair(makeKey(file, i), (*file)[i]));
	}
}

ResultSet FileDB::check()
{
	ResultSet ret;
	for(std::vector<File::Ptr>::iterator f = files_.begin(); f != files_.end(); ++f)
		for(unsigned l = 0; l < (*f)->size() - threshold_; l++)
		{
			File::Ptr fl = *f;
			std::cerr << "\e[K\r" << (*fl)[l]; std::cout.flush();

			std::string key = makeKey(fl, l);
			if (lines_.count(key) <= 1)
				continue;

			std::pair<LinesMultimap::iterator, LinesMultimap::iterator> range;
			range = lines_.equal_range(key);

			Result &res = ret.newResult(threshold_);
			for (LinesMultimap::iterator i = range.first; i != range.second; ++i)
			{
				res.add(i->second);
			}

			while (res.grow((*fl)[l]));
		}

	std::cerr << "\e[K\r"; std::cout.flush();
	return ret;
}


}
