#ifndef FILE_H_INCLUDED_
#define FILE_H_INCLUDED_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "line.h"

namespace analisys {

	class NoSuchLine : public std::runtime_error
	{
	public:
		NoSuchLine(std::string filename) :
			std::runtime_error(std::string("No such line on file") + filename)
		{}
	};

	class File
	{
	public:
		File(std::string filename);

		File(const File &file) : filename_(file.filename()), lines_(file.lines_)
		{
			fixLines_();
		}

		File &operator =(File &file)
		{
			lines_ = file.lines_;
			filename_ = file.filename();
			fixLines_();
		}

		unsigned int size() const;

		const Line &operator [](int n) const;
		Line &operator [](int n);

		bool operator ==(const File &b) const;
		bool operator !=(const File &b) const;

		std::string filename() const
		{
			return filename_;
		}

		friend std::ostream &operator << (std::ostream& out, const File &me)
		{
			return out << me.filename_;
		}

	private:

		void fixLines_()
		{
			for(std::vector<Line>::iterator i = lines_.begin(); i != lines_.end(); ++i)
				i->setFile(this);
		}

		std::string filename_;
		std::vector<Line> lines_;
	};

	inline File::File(std::string filename) : filename_(filename)
	{
		std::fstream file(filename.c_str(), std::fstream::in);

		unsigned int n = 0;
		std::string l;
		while ( !file.eof() )
		{
			std::getline(file, l);
			lines_.push_back(Line(this, n, l));
			n++;
		}

		file.close();
	}

	inline unsigned int File::size() const
	{
		return lines_.size();
	}

	inline const Line &File::operator [](int n) const
	{
		return lines_[n];
	}

	inline Line &File::operator [](int n)
	{
		if (n >= lines_.size() && n < 0)
			throw(NoSuchLine(filename_));

		return lines_[n];
	}

	inline bool File::operator ==(const File &b) const
	{
		return filename_ == b.filename_;
	}

	inline bool File::operator !=(const File &b) const
	{
		return filename_ != b.filename_;
	}
}

#endif
