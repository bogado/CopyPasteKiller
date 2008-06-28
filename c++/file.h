#ifndef FILE_H_INCLUDED_
#define FILE_H_INCLUDED_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "line.h"

namespace analisys {

	class File 
	{
	public:
		File(std::string filename);

		unsigned int size() const;

		const Line &operator [](int n) const;
		Line &operator [](int n);

		bool operator ==(const File &b) const;

		friend std::ostream &operator << (std::ostream& out, const File &me)
		{
			return out << me.filename_;
		}

	private:
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
		return lines_[n];
	}

	inline bool File::operator ==(const File &b) const
	{
		return filename_ == b.filename_;
	}
}

#endif
