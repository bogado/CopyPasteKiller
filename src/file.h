#ifndef FILE_H_INCLUDED_
#define FILE_H_INCLUDED_
 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

#include <memory>

#include "simplifier.h"

namespace analisys {

	class NoSuchFile : public std::runtime_error
	{
	public:
		NoSuchFile(std::string filename) :
			std::runtime_error(std::string("No such file ") + filename)
		{}
	};

	class NoSuchLine : public std::runtime_error
	{
	public:
		NoSuchLine(std::string filename) :
			std::runtime_error(std::string("No such line on file ") + filename)
		{}
	};

	class File
	{
	public:

		typedef std::shared_ptr<File> Ptr;
		typedef std::weak_ptr<File> WeakPtr;

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

			bool same(const Line& l) const
			{
				return (num() == l.num()) && (file() == l.file());
			}

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

			Line(File::Ptr file, unsigned int num, std::string content, const Simplifier& simp) : file_(file), num_(num), content_(content), key_(simp(content))
			{}

			File::WeakPtr file_;
			unsigned num_;
			std::string content_;
			std::string key_;
		};

		static Ptr build(std::string filename, const Simplifier& simp);

		unsigned int size() const;

		const Line &operator [](unsigned n) const;
		Line &operator [](unsigned n);

		bool operator ==(const File &b) const;
		bool operator !=(const File &b) const;

		std::string makeKey(unsigned line, unsigned t);
		std::string makeKey(const Line& line, unsigned t);

		std::string filename() const
		{
			return filename_;
		}

	private:
		File(std::string);

		void init(Ptr file, const Simplifier& simp);

		std::string filename_;
		std::vector<Line> lines_;
	};

	inline const File::Line &File::operator [](unsigned n) const
	{
		return const_cast<const File::Line &>(const_cast<File &>(*this)[n]);
	}

	template <class ch, class tr>
	std::basic_ostream<ch, tr> &operator <<(std::basic_ostream<ch, tr> &out, const File::Line &me)
	{
		out << me.file() << ":" << (me.num() + 1);
		return out;
	}

	template <class ch, class tr>
	std::basic_ostream<ch, tr> &operator << (std::basic_ostream<ch, tr> &out, const File &me)
	{
		return out << me.filename();
	}
}

#endif
