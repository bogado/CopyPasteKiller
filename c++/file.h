#ifndef FILE_H_INCLUDED_
#define FILE_H_INCLUDED_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

#include <tr1/memory>

namespace analisys {

	class NoSuchLine : public std::runtime_error
	{
	public:
		NoSuchLine(std::string filename) :
			std::runtime_error(std::string("No such line on file") + filename)
		{}
	};

	class Line;

	class FileInt
	{
	public:
		virtual unsigned int size() const = 0;

		virtual const Line &operator [](int n) const = 0;
		virtual Line &operator [](int n) = 0;

		virtual bool operator ==(const FileInt &b) const = 0;
		virtual bool operator !=(const FileInt &b) const = 0;

		virtual std::string filename() const = 0;
	};

	inline std::ostream &operator << (std::ostream& out, const FileInt &me)
	{
		return out << me.filename();
	}

	class FileImpl : public FileInt
	{
	public:
		FileImpl(std::string filename);

		unsigned int size() const;

		const Line &operator [](int n) const;
		Line &operator [](int n);

		bool operator ==(const FileInt &b) const;
		bool operator !=(const FileInt &b) const;

		std::string filename() const
		{
			return filename_;
		}

	private:
		std::string filename_;
		std::vector<Line> lines_;
	};

	inline unsigned int FileImpl::size() const
	{
		return lines_.size();
	}

	inline const Line &FileImpl::operator [](int n) const
	{
		if (n >= lines_.size() && n < 0)
			throw(NoSuchLine(filename_));

		return lines_[n];
	}

	inline Line &FileImpl::operator [](int n)
	{
		if (n >= lines_.size() && n < 0)
			throw(NoSuchLine(filename_));

		return lines_[n];
	}

	inline bool FileImpl::operator !=(const FileInt &b) const
	{
		return filename_ != b.filename();
	}

	inline bool FileImpl::operator ==(const FileInt &b) const
	{
		return filename_ == b.filename();
	}

	class File : public FileInt
	{
	public:
		File(std::string filename) : impl_(new FileImpl(filename))
		{}

		virtual unsigned int size() const
		{
			return impl_->size();
		}

		virtual const Line &operator [](int n) const
		{
			return (*impl_)[n];
		}

		virtual Line &operator [](int n)
		{
			return (*impl_)[n];
		}

		virtual bool operator ==(const FileInt &b) const
		{
			return (*impl_) == b;
		}

		virtual bool operator !=(const FileInt &b) const
		{
			return (*impl_) != b;
		}

		virtual std::string filename() const
		{
			return impl_->filename();
		}

	private:
		std::tr1::shared_ptr<FileImpl> impl_;
	};
}

#endif
