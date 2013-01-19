#ifndef __BAG_H__
#define __BAG_H__

#include <vector>
#include <string.h>

#include "../exceptions/BagIndexOutOfBounds.h"

namespace coment
{
	template <class T>
	class Bag
		: public std::vector<T>
	{
	public:
		void set(int id, T value);

		bool remove(T value);

		bool contains(T value);
	};

	template <typename T>
	void Bag<T>::set(int id, T value)
	{
		reserve(id+1);
		resize(id+1);

		(*this)[id] = value;
	}
	
	template <typename T>
	bool Bag<T>::remove(T value)
	{
		// Find value in vector
		for (std::vector<Entity>::iterator it = begin(); it != end(); ++it)
		{
			if (*it == value)
			{
				// Replace with last value and resize array to get rid of last element
				*it = back();

				resize(size()-1);

				return true;
			}
		}

		return false;
	}

	template <typename T>
	bool Bag<T>::contains(T value)
	{
		// Find value in vector
		for (std::vector<Entity>::iterator it = begin(); it != end(); ++it)
		{
			if (*it == value)
			{
				return true;
			}
		}

		return false;
	}
}

#endif /* __BAG_H__ */
