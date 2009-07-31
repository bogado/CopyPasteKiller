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

		Result(int len = 1) : len_(len)
		{}

		void add(const Line &l)
		{
			lines_.push_back(l);
		}

		/** grow this result, if possible
		 *
		 * This will not grow into a trivial (size < 2) result.
		 *
		 * @returns true if it was possible to grow.
		 */
		bool grow(const Line& pivot);

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

		bool operator<(const Result &res) const;

	private:
		LineList lines_;
		unsigned int len_;
	
		/** Verifia se uma linha pode permanecer neste resultado caso ele tenha um novo tamanho
		 * @param line linha pivot a partir da qual este resultado está sendo construido.
		 * @param sz novo tamanho sendo verificado.
		 * @param l linha a ser verificada.
		 */
		bool CanGrow(const Line& line, unsigned sz, const Line& l);

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
