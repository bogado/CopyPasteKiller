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

	class Line;
	class Simplifier;

	class File
	{
	public:
		typedef std::shared_ptr<File> Ptr;
		typedef std::weak_ptr<File> WeakPtr;

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

	inline const Line &File::operator [](unsigned n) const
	{
		return const_cast<const Line &>(const_cast<File &>(*this)[n]);
	}

	inline std::ostream &operator << (std::ostream& out, const File &me)
	{
		return out << me.filename();
	}
}

#endif
