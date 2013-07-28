#ifndef COMENT_COMPMAPUNREGISTERED_H
#define COMENT_COMPMAPUNREGISTERED_H

#include <exception>

namespace coment
{
	class CompMapUnregistered
		: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "A component type without a component map was found";
		}
	};
}

#endif /* COMENT_COMPMAPUNREGISTERED_H */
