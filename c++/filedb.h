#ifndef FILEDB_H_INCLUDED_
#define FILEDB_H_INCLUDED_

#include "file.h"
#include "chunk.h"
#include "result.h"

#include <vector>
#include <tr1/unordered_map>

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

		Result check()
		{
			for(std::vector<File>::iterator f = files_.begin(); f != files_.end(); ++f)
				for(int l = 0; l < f->size(); l++)
				{
					if (lines_.count(f[l].key()))
						continue;

					std::pair<LinesMultimap::iterator, LinesMultimap::iterator> range;
					range = lines_.equal_range(f[l].key());
					Result res;
					for (LinesMultimap::iterator i = range.first; i != range.second; ++i)
						res.add(*i);

					Comparator comp(l);
					while (res.check(1, comp))
					{
						res.grow(1, comp);
						++l;
						if (l == f->size())
							break;
					}
				}
		}

	private:
		std::vector<File> files_;
		LinesMultimap lines_;

		class Comparator 
		{
		public:
			Comparator(const Line &l) line_(l)
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
