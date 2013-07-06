#ifndef __INDEXOUTOFBOUNDS_H__
#define __INDEXOUTOFBOUNDS_H__

#include <exception>

namespace coment
{
	class IndexOutOfBounds
		: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "The index was out of bounds";
		}
	};
}

#endif /* _INDEXOUTOFBOUNDS_H__ */
