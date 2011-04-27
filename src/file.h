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

	class File
	{
	public:
		typedef std::shared_ptr<File> Ptr;
		typedef std::weak_ptr<File> WeakPtr;

		static Ptr build(std::string filename) 
		{
			Ptr file = Ptr(new File(filename));
	
			file->init(file);

			return file;
		}

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
		File(std::string filename) : filename_(filename) 
		{
			struct stat st;
			if (stat(filename.c_str(), &st) || !S_ISREG(st.st_mode))
				throw NoSuchFile(filename);
		}

		void init(Ptr file);

		std::string filename_;
		std::vector<Line> lines_;
	};

	inline unsigned int File::size() const
	{
		return lines_.size();
	}

	inline const Line &File::operator [](unsigned n) const
	{
		return const_cast<const Line &>(const_cast<File &>(*this)[n]);
	}

	inline Line &File::operator [](unsigned n)
	{
		if (n >= lines_.size())
			throw(NoSuchLine(filename_));

		return lines_[n];
	}

	inline std::ostream &operator << (std::ostream& out, const File &me)
	{
		return out << me.filename();
	}
}

#endif
