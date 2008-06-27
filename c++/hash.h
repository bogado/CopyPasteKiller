#ifndef HASH_H_INCLUDED_
#define HASH_H_INCLUDED_

#include <string>
#include <sstream>
#include <stdexcept>
#include <mhash.h>

namespace analisys {

class Hasher
{
public:
	virtual std::string hash(std::string str) = 0;
};

class MhashFailedException : public std::runtime_error
{
public:
	MhashFailedException() : std::runtime_error("mhash failed to init hash")
	{}
};

template <hashid HASH>
class MhashHasher : public Hasher
{
public:
	virtual ~MhashHasher() {}

	class HashBuf
	{
	public:
		unsigned char *buf;
		HashBuf(int size)
		{
			buf = new unsigned char[size];
		}

		~HashBuf()
		{
			delete[] buf;
		}
	};

	virtual std::string hash(std::string str)
	{
		MHASH hasher = mhash_init(HASH);

		if (hasher == MHASH_FAILED)
			throw (MhashFailedException());

		mhash(hasher, str.c_str(), str.size());

		int size = mhash_get_block_size(HASH);

		HashBuf buffer(size);

		mhash_deinit(hasher, buffer.buf);

		std::stringstream result;
		result.setf(std::ios::hex, std::ios::basefield);
		for (int i = 0; i < size; i++)
			result << static_cast<int>(buffer.buf[i]);

		return result.str();
	}
};

typedef MhashHasher<MHASH_MD5> MD5Hasher;

class Hash
{
public:
	static std::string hash(std::string str)
	{
		return instance().calc(str);
	}

	static void set(Hasher *h)
	{
		delete instance().hasher_;
		instance().hasher_ = h;
	}

	std::string calc(std::string str)
	{
		return hasher_->hash(str);
	}

private:
	Hash() : hasher_(new MD5Hasher()) 
	{}

	~Hash()
	{
		delete hasher_;
	}

	static Hash &instance()
	{
		static Hash singleton;
		return singleton;
	}

	Hasher *hasher_;
};

}
#endif
