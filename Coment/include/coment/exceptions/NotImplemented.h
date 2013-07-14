#ifndef __NOTIMPLEMENTED_H__
#define __NOTIMPLEMENTED_H__

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

#endif /* __NOTIMPLEMENTED_H__ */
