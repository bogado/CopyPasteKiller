#ifndef RESULTSET_H_INCLUDED
#define RESULTSET_H_INCLUDED

#include <vector>
#include <iostream>

#include "result.h"
#include "line.h"

namespace analisys {

	class ResultSet
	{
	public:
		typedef std::vector<Result> ResultArr;

		void add(Result r)
		{
			results_.push_back(r);
		}

		Result &newResult()
		{
			results_.push_back(Result());
			return last();
		}

		const Result &operator[](unsigned int i) const
		{
			return results_[i];
		}

		Result &operator[](unsigned int i)
		{
			return results_[i];
		}

		const Result &last() const
		{
			return results_[results_.size() - 1];
		}

		Result &last()
		{
			return results_[results_.size() - 1];
		}

		bool belongs(const Line &l)
		{
			for(ResultArr::iterator i = results_.begin(); i != results_.end(); ++i)
			{
				if (i->belongs(l))
					return true;
			}

			return false;
		}

		friend std::ostream &operator << (std::ostream &out, const ResultSet &me)
		{
			ResultArr::const_iterator begin = me.results_.begin();
			for (ResultArr::const_iterator i = begin; i != me.results_.end(); ++i)
			{
				if (i != begin)
					out << "\n";
				out << *i;
			}
			return out;
		}

		void simplify()
		{
			sort(results_.begin(), results_.end());
			ResultArr::iterator newEnd = unique(results_.begin(), results_.end());
			results_.erase(newEnd, results_.end());
		}

	private:
		ResultArr results_;
	};
}

#endif
