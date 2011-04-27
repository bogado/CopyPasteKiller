#ifndef SIMPLIFIER_H_INCLUDED
#define SIMPLIFIER_H_INCLUDED

#include <string>
#include <vector>
#include <memory>
#include <iostream>

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
	typedef std::shared_ptr<SimplifierInt> Ptr;
	typedef std::vector< Ptr > Vector;

	template <typename Tipo>
	static void setup(Tipo functor)
	{
		instance().add(new SimplifierEncapsuler<Tipo>(functor));
	}

	static std::string doit(std::string str)
	{
		return instance().execute(str);
	}

private:
	Simplifier() : simplifier_()
	{}

	void add(SimplifierInt* simp)
	{
		simplifier_.push_back(Ptr(simp));
	}

	std::string execute(std::string str)
	{
		std::string result = str;

		for(Vector::iterator i = simplifier_.begin(); i != simplifier_.end(); ++i)
		{
			result = (*i)->simplify(result);
		}

		return result;
	}

	static Simplifier& instance()
	{
		static Simplifier singleton;
		return singleton;
	}

	Vector simplifier_;
};

}

#endif
