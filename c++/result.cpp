#include "result.h"

namespace analisys 
{

bool Result::grow(const Line& pivot)
{
	std::vector<bool> newList(lines_.size(), false);

	// Puts all the lines that pass the check on front.
	//			LineList::iterator newEnd = partition(lines_.begin(), lines_.end(),
	//					checker);

	int n = 0;
	int res = lines_.size();
	for (LineList::iterator i = lines_.begin(); i != lines_.end(); ++i)
	{
		if (!CanGrow(pivot, len_ + 1, *i))
		{
			newList[n]= true;
			res--;
		}
		n++;
	}

	// is this a trivial result?
	if (res < 2)
	{
		lines_.sort();
		return false;
	}

	len_++;
	LineList::iterator itr = lines_.begin();
	for (unsigned i = 0; i < newList.size(); i++)
	{
		if (newList[i])
		{
			LineList::iterator old = itr;
			itr++;
			lines_.erase(old);
		} else
			++itr;
	}

	return true;
}

bool Result::CheckLine::operator() (const Line &l)
{
	if (line_.num() < l.num() || line_.num() >= l.num() + size_)
		return false;

	if (l.file() != line_.file())
		return false;

	return true;
}

bool Result::belongs(const Line &l) const
{
	CheckLine checker(l, len_);

	return find_if(lines_.begin(), lines_.end(), checker) != lines_.end();
}

bool Result::belongs(const Result &res) const
{
	for (LineList::const_iterator i = res.lines_.begin(); i != res.lines_.end(); ++i)
	{
		CheckLine checker(*i, len_);
		LineList::const_iterator l = find_if(lines_.begin(), lines_.end(), checker);

		if (l == lines_.end())
		{
			return false;
		}

		if ((i->num() - l->num()) >= len_)
		{
			return false;
		}
	}

	return true;
}

bool Result::CanGrow(const Line& line, unsigned sz, const Line& l)
{
	if (!l.valid(sz) || !line.valid(sz))
		return false;

	for (unsigned i = 0; i < sz; i++)
		if ((l + i) != (line + i))
			return false;

	return true;
}
bool Result::operator==(const Result &res) const
{
	if (res.length() != length())
		return false;

	if (res.size() != size())
		return false;

	LineList::const_iterator j = res.lines_.begin();
	for(LineList::const_iterator i = lines_.begin(); i != lines_.end(); i++)
	{
		if (!((*i) == (*j)))
			return false;
	}

	return true;
}

bool Result::operator<(const Result &res) const
{
	unsigned lenXsiz1 = length() * size();
	unsigned lenXsiz2 = res.length() * res.size();

	if (lenXsiz1 < lenXsiz2)
		return true;

	if (lenXsiz1 > lenXsiz2)
		return false;

	if (length() < res.length())
		return true;

	if (length() > res.length())
		return false;

	return (*lines_.begin()) < (*res.lines_.begin());
}

std::ostream &operator <<(std::ostream &out, const Result &me)
{
	out << me.length() << " (";
	bool first = true;
	for (Result::LineList::const_iterator i = me.lines_.begin(); i != me.lines_.end(); ++i)
	{
		if (!first)
			out << " ";
		else
			first = false;

		out << (*i);
	}
	return out << ")";
}
}

