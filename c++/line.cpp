#include "file.h"

std::ostream &operator <<(std::ostream &out, const analisys::Line &me)
{
	return out << me.file() << ":" << me.num();
}

analisys::Line analisys::Line::operator +(int n) const
{
	return (*file_)[num_ + n];
}

bool analisys::Line::valid(int n) const
{
	if (n <= 0 && n + num_ >= 0)
		return true;

	if (n + num_ < file_->size())
		return true;

	return false;
}
