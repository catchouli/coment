#ifndef COMENT_NOTIMPLEMENTED_H
#define COMENT_NOTIMPLEMENTED_H

#include <exception>

namespace coment
{
	class NotImplemented
		: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Not yet implemented";
		}
	};
}

#endif /* COMENT_NOTIMPLEMENTED_H */
