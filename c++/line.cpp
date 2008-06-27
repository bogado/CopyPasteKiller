#include "file.h"

std::ostream &operator <<(std::ostream &out, const analisys::Line &me)
{
	return out << me.file() << ":" << me.num();
}

