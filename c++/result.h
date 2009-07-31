#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>

#include "line.h"

namespace analisys {

	class Result
	{
	public:
		typedef std::list<Line> LineList;

		Result(const Line &pivot, int len = 1) : pivot_(pivot),  len_(len)
		{}

		void add(const Line &l)
		{
			lines_.push_back(l);
		}

		/** grow this result, if possible
		 * @returns true if it was possible to grow.
		 */
		bool grow();

		/// Length of matching blocks
		unsigned int length() const
		{
			return len_;
		}

		/// Number of lines in this result
		unsigned int size() const
		{
			return lines_.size();
		}

		/// Does the line l belongs to this result?
		bool belongs(const Line &l) const;

		/// Verifica se um resulta pertence a este resultado.
		bool belongs(const Result &res) const;

		friend std::ostream &operator <<(std::ostream &out, const Result &me);

		bool operator==(const Result &res) const;
		bool operator!=(const Result &res) const
		{
			return !(*this == res);
		}

		bool operator<(const Result &res) const;

	private:
		Line pivot_;
		LineList lines_;
		unsigned int len_;
	
		/** Verifia se uma linha pode permanecer neste resultado caso ele tenha um novo tamanho
		 * @param line linha a ser verificada.
		 * @param sz novo tamanho sendo verificado.
		 */
		bool CanGrow(const Line& line, unsigned sz);

		/** Esta classe é um predicado que verifica se uma linha pertence a este resultado.
		 *
		 * usado no teste de 'belongs'
		 */
		class CheckLine
		{
		public:
			CheckLine(const Line& l, unsigned int size) : line_(l), size_(size)
			{}

			bool operator() (const Line &l);

		private:
			const Line &line_;
			unsigned int size_;
		};
	};
}

#endif
