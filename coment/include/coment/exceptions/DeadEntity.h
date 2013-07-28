#ifndef COMENT_DEADENTITY_H
#define COMENT_DEADENTITY_H

#include <exception>

namespace coment
{
	class DeadEntity
		: public std::exception
	{
		virtual const char* what() const throw()
		{
			return "A dead entity was passed to the system";
		}
	};
}

#endif /* COMENT_DEADENTITY_H */
