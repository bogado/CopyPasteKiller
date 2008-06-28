#ifndef FILEDB_H_INCLUDED_
#define FILEDB_H_INCLUDED_

#include "file.h"
#include "chunk.h"

#include <vector>
#include <tr1/unordered_map>

namespace analisys {

	class FileDB
	{
	public:
		void addFile(std::string filename)
		{
			files_.push_back(File(filename));
			File &file = files_[files_.size() -1];

			for(int i = 0; i < file.size(); i++)
				lines_.insert(make_pair(file[i].key(), &file[i]));
		}

		const File &operator[] (unsigned int i) const
		{
			return files_[i];
		}

		unsigned int size() const
		{
			return files_.size();
		}

	private:
		std::vector<File> files_;
		std::tr1::unordered_multimap<std::string, Line*> lines_;
	};
}

#endif
