#ifndef __BAGINDEXOUTOFBOUNDS_H__
#define __BAGINDEXOUTOFBOUNDS_H__

#include <exception>

namespace coment
{
	class BagIndexOutOfBounds
		: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "The bag index was out of bounds";
		}
	};
}

#endif /* __BAGINDEXOUTOFBOUNDS_H__ */
