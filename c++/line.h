#ifndef LINE_H_INCLUDED_
#define LINE_H_INCLUDED_

#include "hash.h"
#include "file.h"
#include <tr1/unordered_map>

namespace analisys {

	class Line
	{
	public:
		std::string key() const
		{
			return key_;
		}

		unsigned int num() const
		{
			return num_;
		}

		const FileInt &file() const
		{
			return *file_;
		}

		std::string content() const
		{
			return content_;
		}

		const Line &operator +(int n) const;

		bool valid(int n = 0) const;

		bool operator== (const Line &l) const
		{
			return l.file() == file() && num_ == l.num();
		}

	private:
		friend class FileImpl;

		Line(const FileInt *file, unsigned int num, std::string content) : file_(file), num_(num), content_(content)
		{
			key_ = Hash::hash(content_);
		}

		const FileInt* file_;
		unsigned int num_;
		std::string content_;
		std::string key_;
	};

	std::ostream &operator <<(std::ostream &out, const Line &me);
}

#endif
