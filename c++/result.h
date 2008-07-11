#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>

#include "line.h"

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
			if (!l.valid(size_) || !line_.valid(size_))
				return false;

			return (l + size_) == (line_ + size_);
		}
	private:
		Line line_;
		unsigned int size_;
	};

	class Result
	{
	public:
		typedef std::list<Line> LineList;

		Result(int len = 1) : len_(len)
		{}

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
			std::vector<bool> newList(lines_.size(), false);
			checker.setSize(len_);
			// Puts all the lines that pass the check on front.
//			LineList::iterator newEnd = partition(lines_.begin(), lines_.end(),
//					checker);

			int n = 0;
			int res = lines_.size();
			for (LineList::iterator i = lines_.begin(); i != lines_.end(); ++i)
			{
				if (!checker(*i))
				{
					newList[n]= true;
					res--;
				}
				n++;
			}

			// is this a trivial result?
			if (res < 2)
			{
				lines_.sort();
				return false;
			}

			len_++;
			LineList::iterator itr = lines_.begin();
			for (int i = 0; i < newList.size(); i++)
			{
				if (newList[i])
				{
					LineList::iterator old = itr;
					itr++;
					lines_.erase(old);
				} else
					++itr;
			}

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

			return find_if(lines_.begin(), lines_.end(), checker) != lines_.end();
		}

		bool belongs(const Result &res) const
		{
			for (LineList::const_iterator i = res.lines_.begin(); i != res.lines_.end(); ++i)
			{
				if (!belongs(*i))
					return false;

				if (i->valid(res.size()) && !belongs(*i + res.size()))
					return false;
			}

			return true;
		}

		friend std::ostream &operator <<(std::ostream &out, const Result &me)
		{
			out << me.length() << " (";
			LineList::const_iterator begin = me.lines_.begin();
			for (LineList::const_iterator i = begin; i != me.lines_.end(); ++i)
			{
				if (i != begin)
					out << ", ";
				out << (*i);
			}
			out << ")";
		}

		bool operator==(const Result &res) const
		{
			if (res.length() != length())
				return false;

			if (res.size() != size())
				return false;

			LineList::const_iterator j = res.lines_.begin();
			for(LineList::const_iterator i = lines_.begin(); i != lines_.end(); i++)
			{
				if (!((*i) == (*j)))
					return false;
			}

			return true;
		}

		bool operator<(const Result &res) const
		{
			if (length() < res.length())
				return true;

			if (length() > res.length())
				return false;

			if (size() < res.size())
				return true;

			if (size() > res.size())
				return false;

			return (*lines_.begin()) < (*res.lines_.begin());
		}

	private:
		class CheckLine
		{
		public:
			CheckLine(const Line& l, unsigned int size) : line_(l), size_(size)
			{}

			bool operator() (const Line &l)
			{
				if (line_.num() < l.num() || line_.num() >= l.num() + size_)
					return false;

				if (l.file() == line_.file())
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
