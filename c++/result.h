#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED

#include <list>

#include "chunk.h"

namespace analisys {

	class Result
	{
	public:
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
		std::list<Line> lines_;
		unsigned int len_;

		/// Check if this line belongs to this result.
		virtual bool check_(const Line &l) const = 0
	};
}

#endif
