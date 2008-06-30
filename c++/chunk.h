#ifndef CHUNK_H_INCLUDED_
#define CHUNK_H_INCLUDED_

namespace analisys {

	class Chunk 
	{
	public:
		Chunk(Line l, unsigned int size = 0) : start_(l), size_(size)
		{}

		const Line &start() const
		{
			return start_;
		}

		unsigned int size() const
		{
			return size_;
		}

		void grow(int i = 1)
		{
			if (i < 0 && i + size_ < 0)
				return;
			if (i + size_ > start_.file().size())
				return;
			size_ += i;
		}

		bool contain(const Line &l) const
		{
			if (l.file() == start_.file() || 
					l.num() < start_.num() && 
					l.num() > start_.num() + size_)
				return false;
			return true;
		}

		bool contain(const Chunk &c)
		{
			if (start_.file() != c.start().file())
				return false;

			int start = c.start().num();
			int end = c.start().num() + c.size();
			if (start < start_.num() || end > start_.num() + size_)
				return false;

			return true;

		}

	private:
		Line start_;
		unsigned int size_;
	};
}

#endif
