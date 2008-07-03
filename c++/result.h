#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED

#include <list>
#include <algorithm>

#include "chunk.h"

namespace analisys {

	class KeyChecker
	{
	public:
		KeyChecker(const Line& l) : line_(l), size_(1)
		{}

		void setSize(unsigned int sz)
		{
			size_ = sz;
		}

		bool operator()(const Line &l)
		{
			return (l + size_) == line_;
		}
	private:
		Line line_;
		unsigned int size_;
	};

	class Result
	{
	public:
		typedef std::list<Line> LineList;

		Result(const Result &r) : lines_(r.lines_), len_(r.len_)
		{ std::cout << this << ":r CC\n"; }

		Result() : len_(1)
		{ std::cout << this << ":r DC\n"; }

		Result(int len) : len_(len)
		{ std::cout << this << ":r C\n"; }

		~Result()
		{ std::cout << this << ":r D\n"; }

		void add(const Line &l)
		{
			lines_.push_back(l);
		}

		/** grow this result, if possible
		 *
		 * This will not grow into a trivial (size < 2) result.
		 *
		 * @returns true if it was possible to grow.
		 */
		template <class ResultChecker>
		bool grow(ResultChecker &checker)
		{
			checker.setSize(len_ + 1);
			// Puts all the lines that pass the check on front.
			LineList::iterator newEnd = partition(lines_.begin(), lines_.end(),
					checker);

			// is this a trivial result?
			if (newEnd == lines_.begin() || newEnd == lines_.begin()++)
				return false;

			len_++;
			lines_.erase(newEnd, lines_.end());
			return true;
		}

		/// Length of matching blocks
		unsigned int length() const
		{
			return len_;
		}

		/// Number of lines in this result
		unsigned int size() const
		{
			return lines_.size();
		}

		/// Does the line l belongs to this result?
		bool belongs(const Line &l) const
		{
			CheckLine checker(l, len_);

			return find_if(lines_.begin(), lines_.end(), checker) == lines_.end();
		}
	private:
		class CheckLine
		{
		public:
			CheckLine(const Line& l, unsigned int size) : line_(l), size_(size)
			{}

			bool operator() (const Line &l)
			{
				if (l.file() != line_.file())
					return false;

				if (l.num() >= line_.num() && l.num() < line_.num() + size_)
					return true;

				return false;
			}

		private:
			const Line &line_;
			unsigned int size_;
		};

		LineList lines_;
		unsigned int len_;
	};
}

#endif
