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

	void add(functor f)
	{
		simplifier_.push_back(f);
	}

	std::string operator()(std::string str) const
	{
		std::string result = str;

		for(auto& i: simplifier_)
		{
			result = i(result);
		}

		return result;
	}

private:
	Vector simplifier_;
};

}

#endif
