#ifndef COMENT_BITINDEXOUTOFBOUNDS_H
#define COMENT_BITINDEXOUTOFBOUNDS_H

#include <exception>

namespace coment
{
	class BitIndexOutOfBounds
		: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "The bitset index was out of bounds";
		}
	};
}

#endif /* COMENT_BITINDEXOUTOFBOUNDS_H */
