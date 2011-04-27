#include "filedb.h"

namespace analisys {

void FileDB::addFile(const std::string& filename)
{
	files_.push_back(File::build(filename, simplifier_));
	File::Ptr file = files_[files_.size() -1];

	if (file->size() < threshold_)
	{
		files_.pop_back();
		return;
	}

	for(unsigned i = 0; i < file->size() - threshold_; i++)
	{
		lines_.insert(make_pair(file->makeKey(i, threshold_), (*file)[i]));
	}
}

ResultSet FileDB::check()
{
	ResultSet ret;
	for(File::Ptr f: files_)
	{
		for(unsigned l = 0; l < f->size() - threshold_; l++)
		{
			std::cerr << "\e[K\r" << (*f)[l]; std::cout.flush();

			std::string key = f->makeKey(l, threshold_);
			if (lines_.count(key) <= 1)
				continue;

			std::pair<LinesMultimap::iterator, LinesMultimap::iterator> range;
			range = lines_.equal_range(key);

			Result res = Result((*f)[l], threshold_);
			for (LinesMultimap::iterator i = range.first; i != range.second; ++i)
			{
				res.add(i->second);
			}

			while (res.grow());
			ret.add(res);
		}
	}

	std::cerr << "\e[K\r"; std::cout.flush();
	return ret;
}


}
