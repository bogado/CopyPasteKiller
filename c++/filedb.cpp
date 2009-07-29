#include "filedb.h"

namespace analisys {

void FileDB::addFile(const std::string& filename)
{
	files_.push_back(File::build(filename));
	File::Ptr file = files_[files_.size() -1];

	for(unsigned i = 0; i < file->size(); i++)
		lines_.insert(make_pair((*file)[i].key(), (*file)[i]));
}

}
