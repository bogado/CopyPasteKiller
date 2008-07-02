#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED

#include <list>

#include "chunk.h"

namespace analisys {

	class Result
	{
	public:
		typedef std::list<Line> LineList;

		Result(int len) : len_(len)
		{}

		void add(const Line &l)
		{
			if (check_(l))
				lines_.push_back(l);
		}

		/** grow this result, if possible
		 *
		 * This will not grow into a trivial (size < 2) result.
		 *
		 * @returns true if it was possible to grow.
		 */
		bool grow(Result &res)
		{
			int n = 0;
			std::vector<bool> keep(lines_.size());
			len_++;
			for (LineList::iterator i = lines_.begin(); i != lines_.end(); ++i)
			{
				if (check_(*i))
				{
					n++;
					keep.push_back(true);
				} else
					keep.push_back(false);
			}

			// trivial result.
			if (n <= 2)
				return false;

			lines_.remove_if(lines_.begin(), lines_.end(), /* keep */);
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

	private:
		LineList lines_;
		unsigned int len_;

		/// Check if this line belongs to this result.
		virtual bool check_(const Line &l) const = 0;
	};
}

#endif
