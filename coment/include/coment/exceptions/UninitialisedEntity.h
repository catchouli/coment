#ifndef COMENT_UNINITIALISEDENTITY_H
#define COMENT_UNINITIALISEDENTITY_H

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

#endif /* COMENT_UNINITIALISEDENTITY_H */
