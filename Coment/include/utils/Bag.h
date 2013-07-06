#ifndef __BAG_H__
#define __BAG_H__

#include <stdlib.h>
#include <stdio.h>

namespace coment
{
	// The size of the dynamic array is the the number of elements,
	// while the capacity is how many elements could exist in the memory that's allocated
	template <typename T>
	class Bag
	{
	public:
		Bag();
		~Bag();

		void add(const T& value);

		void remove(size_t i);
		void remove(const T& value);

		void removeAll(const T& value);

		T popBack();

		void clear();

		size_t contains(const T& value);

		void reserve(size_t n);
		void resize(size_t n);

		void setData(T* data);
		void setSize(size_t n);
		void setCapacity(size_t n);

		virtual void grow();

		inline size_t getSize() const;
		inline size_t getCapacity() const;

		void set(size_t i, const T& value);

		T& get(const size_t i);

		T& operator[](const int i);

	private:
		T* _data;

		size_t _size;
		size_t _capacity;
	};

	template <typename T>
	Bag<T>::Bag()
		: _data(nullptr), _size(0), _capacity(0)
	{

	}

	template <typename T>
	Bag<T>::~Bag()
	{
		free(_data);
		printf("~Bag()\n");
	}

	// Add an element to the collection, increasing the capacity if necessary
	template <typename T>
	void Bag<T>::add(const T& value)
	{
		resize(_size+1);
		_data[_size-1] = value;
	}

	// Remove the element at i
	// by swapping the last element with it and resizing the elemnt down by 1
	template <typename T>
	void Bag<T>::remove(size_t i)
	{
		_data[i] = _data[_size-1];
		resize(_size-1);
	}

	// Remove the first occurence of value
	// by swapping the last element with it and resizing the elemnt down by 1
	template <typename T>
	void Bag<T>::remove(const T& value)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data[i] == value)
			{
				_data[i] = _data[_size-1];
				resize(_size-1);

				return;
			}
		}
	}

	// Remove the first occurence of value
	// by swapping the last element with it and resizing the elemnt down by 1
	template <typename T>
	void Bag<T>::removeAll(const T& value)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data[i] == value)
			{
				_data[i] = _data[_size-1];
				resize(_size-1);

				--i;
			}
		}
	}

	// Remove the last element and return it
	template <typename T>
	T Bag<T>::popBack()
	{
		resize(_size-1);
		return _data[_size];
	}

	template <typename T>
	void Bag<T>::clear()
	{
		_size = 0;
	}

	// Returns the index of the first occurence of value
	// (or -1 if it's not in the array)
	template <typename T>
	size_t Bag<T>::contains(const T& value)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data[i] == value)
			{
				return i;
			}
		}

		return -1;
	}

	// Allocate the memory for up to n elements
	template <typename T>
	void Bag<T>::reserve(size_t n)
	{
		while (_capacity < n)
			grow();
	}

	// Reserve the memory for at least n elements and increase the size to n
	template <typename T>
	void Bag<T>::resize(size_t n)
	{
		reserve(n);

		_size = n;
	}

	// Set the data pointer
	template <typename T>
	void Bag<T>::setData(T* data)
	{
		_data = data;
	}

	// Set the size
	template <typename T>
	void Bag<T>::setSize(size_t n)
	{
		_size = n;
	}

	// Set the capacity of the array, reallocating the memory and discarding any elements data past element n
	template <typename T>
	void Bag<T>::setCapacity(size_t n)
	{
		_capacity = n;

		_data = (T*)realloc(_data, _capacity * sizeof(T));
	}

	// Grow the dynamic array's allocated memory
	// Override this to change behaviour - default is to double capacity (or set it to 1 if it's 0)
	template <typename T>
	void Bag<T>::grow()
	{
		if (_capacity == 0)
			setCapacity(1);
		else
			setCapacity(_capacity * 2);
	}

	// Get the current size of the array
	template <typename T>
	size_t Bag<T>::getSize() const
	{
		return _size;
	}

	// Get the current capacity of the array
	template <typename T>
	size_t Bag<T>::getCapacity() const
	{
		return _capacity;
	}

	// Set the element i to the value of value
	template <typename T>
	void Bag<T>::set(size_t i, const T& value)
	{
		resize(i+1);
		_data[i] = value;
	}

	// Get reference to element i
	template <typename T>
	T& Bag<T>::get(const size_t i)
	{
		return _data[i];
	}

	// Get reference to element i
	template <typename T>
	T& Bag<T>::operator[](const int i)
	{
		return _data[i];
	}
}

#endif /* __BAG_H__ */
