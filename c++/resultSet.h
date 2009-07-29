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
		ResultSet() : threshold_(4)
		{}

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
			bool first = true;
			for (ResultArr::const_iterator i = me.results_.begin(); i != me.results_.end(); ++i)
			{
				if (i->length() > me.threshold_)
				{
					if (!first)
					{
						out << "\n";
					}

					out << *i;
					first = false;
				}
			}
			return out;
		}

		void simplify()
		{
			sort(results_.begin(), results_.end());
			ResultArr::iterator newEnd = unique(results_.begin(), results_.end());
			results_.erase(newEnd, results_.end());

			unsigned passo = 0;
			std::vector<bool> include(results_.size(), true);
			for (ResultArr::reverse_iterator i = results_.rbegin(); i != results_.rend(); i++)
			{
				int n = 0;
				for (ResultArr::reverse_iterator j = (--results_.rend()); j != i; ++n, --j)
				{
					if ((*i).belongs(*j))
					{
						include[n] = false;
					}
				}

				std::cerr << "\e[K\r" << passo*100/results_.size() << "%"; std::cout.flush();
				passo ++;
			}

			std::cerr << "\e[K\r"; std::cout.flush();

			int i = 0;
			for (ResultArr::iterator j = results_.begin(); j != results_.end(); ++i)
			{
				if (include[i])
				{
					++j;
				} else {
					results_.erase(j);
				}
			}
		}

		void setPrintThresshold(unsigned t)
		{
			threshold_ = t;
		}

	private:
		unsigned threshold_;
		ResultArr results_;
	};
}

#endif
