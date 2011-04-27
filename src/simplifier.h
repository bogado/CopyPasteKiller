#ifndef SIMPLIFIER_H_INCLUDED
#define SIMPLIFIER_H_INCLUDED

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>

namespace analisys {

class Simplifier
{
public:
	typedef std::function<std::string(const std::string&)> functor;
	typedef std::vector<functor> Vector;

	template <typename Tipo>
	static void setup(Tipo functor)
	{
		instance().add(functor);
	}

	static std::string doit(std::string str)
	{
		return instance().execute(str);
	}

private:
	Simplifier() : simplifier_()
	{}

	void add(functor simp)
	{
		simplifier_.push_back(simp);
	}

	std::string execute(std::string str)
	{
		std::string result = str;

		for(auto& i: simplifier_)
		{
			result = i(result);
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
