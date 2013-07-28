#ifndef COMENT_INDEXOUTOFBOUNDS_H
#define COMENT_INDEXOUTOFBOUNDS_H

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

#endif /* COMENT_INDEXOUTOFBOUNDS_H */
