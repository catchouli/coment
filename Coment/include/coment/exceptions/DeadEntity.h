#ifndef __DEADENTITY_H__
#define __DEADENTITY_H__

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

#endif /* __DEADENTITY_H__ */
