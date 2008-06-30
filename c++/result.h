#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED

#include <list>

#include "chunk.h"

namespace analisys {

	class Result
	{
	public:
		void grow(int n);

	private:
		std::list<Line> Lines;
		unsigned int size;
	};
}

#endif
