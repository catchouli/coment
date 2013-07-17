#ifndef __UNINITIALISEDENTITY_H__
#define __UNINITIALISEDENTITY_H__

#include <exception>

namespace coment
{
	class UninitialisedEntity
		: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "An entity was passed to the system which was not initialised by the system";
		}
	};
}

#endif /* __UNINITIALISEDENTITY_H__ */
