#ifndef LINE_H_INCLUDED_
#define LINE_H_INCLUDED_

#include "hash.h"
#include "file.h"
#include <tr1/unordered_map>

namespace analisys {

	class File;

	class Line
	{
	public:
		Line(const File *file, unsigned int num, std::string content) : file_(file), num_(num), content_(content)
		{
			key_ = Hash::hash(content_);
		}

		std::string key() const
		{
			return key_;
		}

		unsigned int num() const
		{
			return num_;
		}

		const File &file() const
		{
			return *file_;
		}

		std::string content() const
		{
			return content_;
		}

	private:
		const File* file_;
		unsigned int num_;
		std::string content_;
		std::string key_;
	};

}

std::ostream &operator <<(std::ostream &out, const analisys::Line &me);

#endif
