#ifndef LINE_H_INCLUDED_
#define LINE_H_INCLUDED_

#include "file.h"
#include "simplifier.h"

#include <unordered_map>

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

		const File::Ptr file() const
		{
			return file_.lock();
		}

		std::string content() const
		{
			return content_;
		}

		const Line &operator +(int n) const
		{
			return (*file())[num_ + n];
		}

		bool valid(unsigned n = 0) const;

		bool operator!= (const Line &l) const
		{
			return !(l.key() == key());
		}

		bool operator== (const Line &l) const
		{
			return l.key() == key();
		}

		bool operator< (const Line &l) const
		{
			if (file() != l.file())
			{
				return file()->filename() < l.file()->filename();
			}

			return num_ < l.num_;
		}

	private:
		friend class File;

		Line(File::Ptr file, unsigned int num, std::string content) : file_(file), num_(num), content_(content), key_(Simplifier::doit(content))
		{}

		File::WeakPtr file_;
		unsigned num_;
		std::string content_;
		std::string key_;
	};

	std::ostream &operator <<(std::ostream &out, const Line &me);
}

#endif
