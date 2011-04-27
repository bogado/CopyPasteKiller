#include "result.h"

#include <cstdlib>

namespace analisys 
{

bool Result::grow()
{
	std::vector<bool> removeThis(lines_.size(), false);

	// Puts all the lines that pass the check on front.
	//			LineList::iterator newEnd = partition(lines_.begin(), lines_.end(),
	//					checker);

	int n = 0;
	int res = lines_.size();
	for (Line& i : lines_)
	{
		if (!CanGrow(i, len_ + 1))
		{
			removeThis[n]= true;
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
	for (unsigned i = 0; i < removeThis.size(); i++)
	{
		if (removeThis[i])
		{
			LineList::iterator old = itr;
			++itr;
			lines_.erase(old);
		} else
			++itr;
	}

	return true;
}

bool Result::belongs(const Line &line) const
{
	return find_if(lines_.begin(), lines_.end(), [&](const Line& l)
	{
		if (line.num() < l.num() || line.num() >= l.num() + len_)
			return false;

		if (l.file() != line.file())
			return false;

		return true;
	}) != lines_.end();
}

bool Result::belongs(const Result &res) const
{
	if (res.size() > size())
	{
		return false;
	}

	if (res.length() > length())
	{
		return false;
	}

	for (Line i: res.lines_)
	{
		LineList::const_iterator l = min_element(lines_.begin(), lines_.end(), [&](const Line& a, const Line& b)
		{
			if (a.file() != b.file() || a.file() != i.file())
				return false;

			return abs(i.num() - a.num()) < abs(i.num() - b.num());
		});

		if (l == lines_.end())
		{
			return false;
		}

		if (l->num() + res.length() > i.num() + length())
		{
			return false;
		}
	}

	return true;
}

bool Result::CanGrow(const Line& line, unsigned sz)
{
	if (line.same(pivot_))
		return true;

	if (!line.valid(sz) || !pivot_.valid(sz))
	{
		return false;
	}

	return line.file()->makeKey(line, sz) == pivot_.file()->makeKey(pivot_, sz);
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
	for (Line i: me.lines_)
	{
		if (!first)
			out << " ";
		else
			first = false;

		out << i;

		if (i.same(me.pivot_))
			out << "*";
	}

	out << ")";

	if (me.verbose_)
	{
		out << "\n";
		for (int i = 0; i < me.length(); i++)
		{
			out << (me.pivot_ + i).content() << "\n";
		}
	}

	return out;
}

}

