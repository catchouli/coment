#ifndef __BITINDEXOUTOFBOUNDS_H__
#define __BITINDEXOUTOFBOUNDS_H__

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

#endif /* __BITINDEXOUTOFBOUNDS_H__ */
