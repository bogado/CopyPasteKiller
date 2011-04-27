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
		FileDB(unsigned threshold, Simplifier simplifier) :
			threshold_(threshold),
			simplifier_(simplifier)
		{}

		typedef std::unordered_multimap<std::string, Line> LinesMultimap;

		void addFile(const std::string& filename);

		const File::Ptr &operator[] (unsigned int i) const
		{
			return files_[i];
		}

		unsigned int size() const
		{
			return files_.size();
		}

		ResultSet check();

	private:
		unsigned threshold_;
		std::vector<File::Ptr> files_;
		LinesMultimap lines_;
		Simplifier simplifier_;
	};
}

#endif
