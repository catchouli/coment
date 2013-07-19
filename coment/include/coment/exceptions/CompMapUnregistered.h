#ifndef __COMPMAPUNREGISTERED_H__
#define __COMPMAPUNREGISTERED_H__

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

#endif /* __COMPMAPUNREGISTERED_H__ */
