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

		void dropLast()
		{
			results_.pop_back();
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

		void setVerbose(bool v = false)
		{
			for (ResultArr::iterator i = results_.begin(); i != results_.end(); ++i)
				i->setVerbose(v);
		}

		bool belongs(const Result& obj)
		{
			if (results_.size() == 0)
				return false;

			for(ResultArr::iterator i = results_.begin(); i != results_.end(); ++i)
			{
				if ((obj != *i) && i->belongs(obj))
				{
					return true;
				}
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

			unsigned passo = 0;
			std::vector<bool> include(results_.size(), true);
			for (ResultArr::iterator i = results_.begin(); i != results_.end(); i++)
			{
				int n = 0;
				for (ResultArr::iterator j = results_.begin(); j != results_.end(); ++n, ++j)
				{
					if (i == j || !include[n])
						continue;

					if ((*i).belongs(*j))
					{
						include[n] = false;
					}
				}

				std::cerr << "\e[K\r" << passo*100/results_.size() << "%"; std::cerr.flush();
				passo ++;
			}

			std::cerr << "\e[K\r"; std::cerr.flush();

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

	private:
		ResultArr results_;
	};
}

#endif
