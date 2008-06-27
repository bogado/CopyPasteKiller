#ifndef LINE_H_INCLUDED_
#define LINE_H_INCLUDED_

#include <hash.h>
#include <file.h>
#include <tr1/unordered_map>

namespace analisys {

	class Line : public Object
	{
	public:
		Line(const File &file, int num, string content);

		std::string key() const
		{
			return key_;
		}

		int num() const
		{
			return num_;
		}

		std::string content() const
		{
			return content_;
		}

	private:
		const File &file_;
		const int num;
		std::string content_;
		std::string key_;
	};

	class LineDB
	{
	public:

		void add(Line &l);

		Line &operator[](std::string key); //?

	private:
		std::tr1::unordered_map<std::string, Line> lines_; 
	};
}

#endif
