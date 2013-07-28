#ifndef COMENT_BITCOUNTOUTOFRANGE_H
#define COMENT_BITCOUNTOUTOFRANGE_H

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

#endif /* COMENT_BITCOUNTOUTOFRANGE_H */
