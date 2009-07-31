#include "line.h"

namespace analisys {

	std::ostream &operator <<(std::ostream &out, const Line &me)
	{
		return out << (*me.file()) << ":" << (me.num() + 1);
	}

	bool Line::valid(unsigned n) const
	{
		if (n + num_ < file()->size())
			return true;

		return false;
	}
}
