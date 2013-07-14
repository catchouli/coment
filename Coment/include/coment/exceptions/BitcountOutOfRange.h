#ifndef __BITCOUNTOUTOFRANGE_H__
#define __BITCOUNTOUTOFRANGE_H__

#include <exception>

namespace coment
{
	class BitcountOutOfRange
		: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "The bitcount was out of range";
		}
	};
}

#endif /* __BITCOUNTOUTOFRANGE_H__ */
