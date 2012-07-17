#ifndef __BAG_H__
#define __BAG_H__

#include <string.h>

#include "../exceptions/BagIndexOutOfBounds.h"

namespace coment
{
	template <class T>
	class Bag
	{
	public:
		Bag(int capacity = 10);
		Bag(const Bag& bag);
		~Bag();

		void initialise();
		
		T& get(unsigned int index);
		const T& get(unsigned int index) const;
		
		T& getLast();
		const T& getLast() const;

		void remove(unsigned int index);
		void removeLast();
		T popLast();
		
		void add(const T& value);

		void set(unsigned int index, const T& value);

		void clear();

		bool contains(const T& value);
		int getIndex(const T& value);

		unsigned int getSize() const;

		unsigned int getCapacity() const;

	private:
		void grow();
		void grow(unsigned int newCapacity);

		unsigned int _size;
		unsigned int _capacity;

		T* _data;
	};
	
	template <typename T>
	Bag<T>::Bag(int capacity)
		: _data(NULL), _size(0), _capacity(capacity)
	{
		initialise();

		grow(capacity);
	}
	
	template <typename T>
	Bag<T>::Bag(const Bag<T>& bag)
		: _data(NULL)
	{
		_data = new T[bag._capacity];

		_size = bag._size;
		_capacity = bag._capacity;
		memcpy(_data, bag._data, sizeof(T) * bag._capacity);
	}
	
	template <typename T>
	Bag<T>::~Bag()
	{
		delete[] _data;
	}

	template <typename T>
	void Bag<T>::initialise()
	{
		_size = 0;
		_capacity = 0;
		_data = 0;
	}

	template <typename T>
	T& Bag<T>::get(unsigned int index)
	{
		// Return the item
		return _data[index];
	}

	template <typename T>
	const T& Bag<T>::get(unsigned int index) const
	{
		// Return the item
		return _data[index];
	}

	template <typename T>
	T& Bag<T>::getLast()
	{
		// If there's an element to get, get it
		if (_size > 0)
			return _data[_size-1];
		else
			throw BagIndexOutOfBounds();
	}

	template <typename T>
	const T& Bag<T>::getLast() const
	{
		// If there's an element to get, get it
		if (_size > 0)
			return _data[_size-1];
		else
			throw BagIndexOutOfBounds();
	}
	
	template <typename T>
	void Bag<T>::remove(unsigned int index)
	{
		// If the index is out of bounds
		if (index >= _size)
		{
			// This element doesn't exist in the bag
			throw BagIndexOutOfBounds();
		}

		// Swap an item from the end of the bag to this index to remove it
		_data[index] = _data[--_size];
	}

	template <typename T>
	void Bag<T>::removeLast()
	{
		// If there's an element to remove, remove it
		if (_size > 0)
			_size--;
		else
			throw BagIndexOutOfBounds();
	}

	template <typename T>
	T Bag<T>::popLast()
	{
		// If there's an element to remove, remove it
		if (_size > 0)
		{

			_size--;
			return _data[_size--];
		}
		else
		{
			throw BagIndexOutOfBounds();
		}
	}
	
	template <typename T>
	void Bag<T>::add(const T& value)
	{
		if (_size == _capacity)
			grow();

		_data[_size++] = value;
	}
	
	template <typename T>
	void Bag<T>::set(unsigned int index, const T& value)
	{
		while (index >= _capacity)
		{
			// Make sure the bag is large enough to contain element at this index
			grow();
		}

		if (_size < index + 1)
			_size = index + 1;

		// Set value
		_data[index] = value;
	}
	
	template <typename T>
	void Bag<T>::clear()
	{
		_size = 0;
	}
	
	template <typename T>
	bool Bag<T>::contains(const T& value)
	{
		// Iterate through bag
		for (unsigned int i = 0; i < _size; ++i)
		{
			// If the element is found, return true
			if (_data[i] == value)
				return true;
		}

		return false;
	}
	
	template <typename T>
	int Bag<T>::getIndex(const T& value)
	{
		// Iterate through bag
		for (unsigned int i = 0; i < _size; ++i)
		{
			// If the element is found, return true
			if (_data[i] == value)
				return i;
		}

		return -1;
	}
	
	template <typename T>
	unsigned int Bag<T>::getSize() const
	{
		return _size;
	}
	
	template <typename T>
	unsigned int Bag<T>::getCapacity() const
	{
		return _capacity;
	}
	
	template <typename T>
	void Bag<T>::grow()
	{
		// Increase the capacity by 50%
		_capacity = (unsigned int)(_capacity * 1.5f);
		_capacity++;
		grow(_capacity);
	}
	
	template <typename T>
	void Bag<T>::grow(unsigned int newCapacity)
	{
		T* temp = new T[newCapacity];
		memset(temp, 0, sizeof(T) * newCapacity);

		// Copy and delete the original data if it exists
		if (_data)
		{
			memcpy(temp, _data, _size * sizeof(T));
			delete[] _data;
		}

		// Set the data to the location of our data
		_data = temp;
		_capacity = newCapacity;
	}
}

#endif /* __BAG_H__ */
