#ifndef SIMPLIFIER_H_INCLUDED
#define SIMPLIFIER_H_INCLUDED

#include <string>

namespace analisys {

class SimplifierInt 
{
public:
	virtual ~SimplifierInt() {}

	virtual std::string simplify(const std::string& str) = 0;
};

template <typename Tipo>
class SimplifierEncapsuler : public SimplifierInt
{
public:
	SimplifierEncapsuler(Tipo functor) : functor_(functor)
	{}

	std::string simplify(const std::string& str)
	{
		return functor_(str);
	}

private:
	Tipo functor_;
};

class Simplifier
{
public:
	template <typename Tipo>
	static void setup(Tipo functor)
	{
		setupSimplifier(new SimplifierEncapsuler<Tipo>(functor));
	}

	static void setupSimplifier(SimplifierInt* simp)
	{
		simplifier_ = simp;
	}

	static std::string simplify(const std::string& str)
	{
		if (simplifier_ == NULL)
			return str;

		return simplifier_->simplify(str);
	}

private:
	static SimplifierInt* simplifier_;
};

}

#endif
