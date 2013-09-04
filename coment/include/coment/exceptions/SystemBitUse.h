#ifndef COMENT_SYSTEMBITUSE_H
#define COMENT_SYSTEMBITUSE_H

#include <exception>

namespace coment
{
	class SystemBitUse
		: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "A system may only reference a component in one of it's masks (inclusion, or exclusion).";
		}
	};
}

#endif /* COMENT_SYSTEMBITUSE_H */
