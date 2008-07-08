#include "line.h"

namespace analisys {

	std::ostream &operator <<(std::ostream &out, const Line &me)
	{
		return out << me.file() << ":" << (me.num() + 1);
	}

	const Line &analisys::Line::operator +(int n) const
	{
		return (*file_)[num_ + n];
	}

	bool Line::valid(int n) const
	{
		if (n <= 0 && n + num_ >= 0)
			return true;

		if (n + num_ < file_->size())
			return true;

		return false;
	}

}
