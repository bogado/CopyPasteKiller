#ifndef FILEDB_H_INCLUDED_
#define FILEDB_H_INCLUDED_

#include "file.h"
#include "result.h"
#include "resultSet.h"

#include <vector>
#include <unordered_map>

namespace analisys {

	class FileDB
	{
	public:
		typedef std::tr1::unordered_multimap<std::string, Line> LinesMultimap;

		void addFile(std::string filename)
		{
			files_.push_back(File(filename));
			File &file = files_[files_.size() -1];

			for(int i = 0; i < file.size(); i++)
				lines_.insert(make_pair(file[i].key(), file[i]));
		}

		const File &operator[] (unsigned int i) const
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
			for(std::vector<File>::iterator f = files_.begin(); f != files_.end(); ++f)
				for(int l = 0; l < f->size(); l++)
				{
					std::cout << "\e[K\r" << (*f)[l]; std::cout.flush();

					if (lines_.count((*f)[l].key()) <= 1)
						continue;

					std::pair<LinesMultimap::iterator, LinesMultimap::iterator> range;
					range = lines_.equal_range((*f)[l].key());
					Result &res = ret.newResult();
					for (LinesMultimap::iterator i = range.first; i != range.second; ++i)
						res.add(i->second);

					KeyChecker resultChecker((*f)[l]);

					while (res.grow(resultChecker))
					{
						++l;
					}
				}
			return ret;
		}

	private:
		std::vector<File> files_;
		LinesMultimap lines_;

		class Comparator
		{
		public:
			Comparator(const Line &l) : line_(l)
			{}

			bool operator()(const Line &l)
			{
				return l == line_;
			}
		private:
			const Line &line_;
		};
	};
}

#endif
