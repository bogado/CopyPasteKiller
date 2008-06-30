#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED

#include <list>

#include "chunk.h"

namespace analisys {

	class Result
	{
	public:
		template <class FUNCTOR>
		void grow(int n, FUNCTOR f)
		{
			Check<FUNCTOR> c(n, f);
			lines_.remove_if(c);
		}

	private:
		std::list<Line> lines_;
		unsigned int size_;

		template<class FUNCTOR>
		class Check
		{
		public:
			Check(int n, FUNCTOR f) : n_(n), f_(f)
			{}

			bool operator()(const Line &l)
			{
				if (l.valid(n_) && f_(l + n_))
					return true;

				return false;
			}
		private:
			int n_;
			FUNCTOR f_;
		};
	};
}

#endif
