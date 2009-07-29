#ifndef FILEDB_H_INCLUDED_
#define FILEDB_H_INCLUDED_

#include "file.h"
#include "result.h"
#include "resultSet.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace analisys {

	class FileDB
	{
	public:
		typedef std::tr1::unordered_multimap<std::string, Line> LinesMultimap;

		void addFile(const std::string& filename);

		const File::Ptr &operator[] (unsigned int i) const
		{
			return files_[i];
		}

		unsigned int size() const
		{
			return files_.size();
		}

		ResultSet check()
		{
			ResultSet ret;
			for(std::vector<File::Ptr>::iterator f = files_.begin(); f != files_.end(); ++f)
				for(unsigned l = 0; l < (*f)->size(); l++)
				{
					File::Ptr fl = *f;
					std::cout << "\e[K\r" << (*fl)[l]; std::cout.flush();

					if (lines_.count((*fl)[l].key()) <= 1)
						continue;

					std::pair<LinesMultimap::iterator, LinesMultimap::iterator> range;
					range = lines_.equal_range((*fl)[l].key());
					Result &res = ret.newResult();
					for (LinesMultimap::iterator i = range.first; i != range.second; ++i)
						res.add(i->second);

					KeyChecker resultChecker((*fl)[l]);

					while (res.grow(resultChecker))
					{
						++l;
					}
				}
			return ret;
		}

	private:
		std::vector<File::Ptr> files_;
		LinesMultimap lines_;
	};
}

#endif
