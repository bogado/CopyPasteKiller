#include "line.h"

namespace analisys {

	std::ostream &operator <<(std::ostream &out, const Line &me)
	{
		return out << (*me.file()) << ":" << (me.num() + 1);
	}

	const Line &analisys::Line::operator +(int n) const
	{
		return (*file())[num_ + n];
	}

	bool Line::valid(unsigned n) const
	{
		if (n + num_ < file()->size())
			return true;

		return false;
	}
}
