#ifndef COMENT_BITSET_H
#define COMENT_BITSET_H

#include <string.h>
#include <stdint.h>

#include "../exceptions/NotImplemented.h"
#include "../exceptions/BitcountOutOfRange.h"
#include "../exceptions/BitIndexOutOfBounds.h"

namespace coment
{
	template <int bitcount>
	class Bitset
	{
	public:
		Bitset();
		Bitset(const Bitset<bitcount>& other);
		Bitset(const unsigned int other);
		~Bitset();

		Bitset<bitcount>& operator=(const Bitset<bitcount>& other);
		Bitset<bitcount>& operator=(const int rhs);

		bool operator==(const Bitset<bitcount>& other) const;

		bool operator!=(const Bitset<bitcount>& other) const;

		Bitset<bitcount>& operator<<=(unsigned int dist);
		Bitset<bitcount> operator<<(unsigned int dist) const;

		Bitset<bitcount>& operator>>=(unsigned int dist);
		Bitset<bitcount> operator>>(unsigned int dist) const;

		Bitset<bitcount>& operator&=(const Bitset<bitcount>& other);
		const Bitset<bitcount> operator&(const Bitset<bitcount>& other) const;

		Bitset<bitcount>& operator|=(const Bitset<bitcount>& other);
		const Bitset<bitcount> operator|(const Bitset<bitcount>& other) const;

		bool operator[](unsigned int rhs) const;

		void setBit(unsigned int index);
		void clearBit(unsigned int index);
		void toggleBit(unsigned int index);

		bool isZero() const;

		void clear();

		uint32_t* getData();
		const uint32_t* getData() const;
		uint32_t getDataSize() const;

	private:
		uint32_t _words[bitcount/32];
	};

	template <int bitcount>
	Bitset<bitcount>::Bitset()
	{
		memset(_words, 0, (bitcount/32) * sizeof(uint32_t));
	}

	template <int bitcount>
	Bitset<bitcount>::Bitset(const Bitset<bitcount>& other)
	{
		memset(_words, 0, (bitcount/32) * sizeof(uint32_t));

		for (uint32_t i = 0; i < bitcount/32; ++i)
		{
			_words[i] = other._words[i];
		}
	}

	template <int bitcount>
	Bitset<bitcount>::Bitset(const unsigned int other)
	{
		memset(_words, 0, (bitcount/32) * sizeof(uint32_t));

		if ((bitcount/32) > 0)
		{
			_words[0] = other;
		}
	}

	template <int bitcount>
	Bitset<bitcount>::~Bitset()
	{

	}

	template <int bitcount>
	Bitset<bitcount>& Bitset<bitcount>::operator=(const Bitset<bitcount>& other)
	{
		for (uint32_t i = 0; i < (bitcount/32); ++i)
		{
			_words[i] = other._words[i];
		}

		return *this;
	}

	template <int bitcount>
	Bitset<bitcount>& Bitset<bitcount>::operator=(const int rhs)
	{
		if ((bitcount/32) > 0)
			_words[0] = rhs;

		return *this;
	}

	template <int bitcount>
	bool Bitset<bitcount>::operator==(const Bitset<bitcount>& other) const
	{
		for (uint32_t i = 0; i < (bitcount/32); ++i)
		{
			if (_words[i] != other._words[i])
				return false;
		}

		return true;
	}

	template <int bitcount>
	bool Bitset<bitcount>::operator!=(const Bitset<bitcount>& other) const
	{
		return !(*this == other);
	}

	template <int bitcount>
	Bitset<bitcount>& Bitset<bitcount>::operator<<=(unsigned int dist)
	{
		if (dist < 0 || dist >= 32)
			throw NotImplemented();

		if ((bitcount/32) > 0)
		{
			uint32_t oldWord = 0;
			for (uint32_t i = 0; i < (bitcount/32); ++i)
			{
				uint32_t nextWord = _words[i];

				_words[i] <<= dist;
				_words[i] |= oldWord >> (32 - dist);

				oldWord = nextWord;
			}
		}

		return *this;
	}

	template <int bitcount>
	Bitset<bitcount> Bitset<bitcount>::operator<<(unsigned int dist) const
	{
		Bitset<bitcount> result = *this;

		result <<= dist;

		return result;
	}

	template <int bitcount>
	Bitset<bitcount>& Bitset<bitcount>::operator>>=(unsigned int dist)
	{
		if (dist < 0 || dist >= 32)
			throw NotImplemented();

		if ((bitcount/32) > 0)
		{
			for (uint32_t i = 0; i < (bitcount/32); ++i)
			{
				_words[i] >>= dist;

				if (i + 1 < (bitcount/32))
					_words[i] |= _words[i+1] << (32 - dist);
			}
		}

		return *this;
	}

	template <int bitcount>
	Bitset<bitcount> Bitset<bitcount>::operator>>(unsigned int dist) const
	{
		Bitset<bitcount> result = *this;

		result >>= dist;

		return result;
	}

	template <int bitcount>
	Bitset<bitcount>& Bitset<bitcount>::operator&=(const Bitset<bitcount>& other)
	{
		for (uint32_t i = 0; i < (bitcount/32); ++i)
		{
			_words[i] &= other._words[i];
		}

		return *this;
	}

	template <int bitcount>
	const Bitset<bitcount> Bitset<bitcount>::operator&(const Bitset<bitcount>& other) const
	{
		Bitset<bitcount> result(*this);

		result &= other;

		return result;
	}

	template <int bitcount>
	Bitset<bitcount>& Bitset<bitcount>::operator|=(const Bitset<bitcount>& other)
	{
		for (uint32_t i = 0; i < (bitcount/32); ++i)
		{
			_words[i] |= other._words[i];
		}

		return *this;
	}

	template <int bitcount>
	const Bitset<bitcount> Bitset<bitcount>::operator|(const Bitset<bitcount>& other) const
	{
		Bitset<bitcount> result(*this);

		result |= other;

		return result;
	}

	// Get bit at position
	template <int bitcount>
	bool Bitset<bitcount>::operator[](unsigned int rhs) const
	{
		// Get word for this bit
		unsigned int word = rhs / 32;

		if (rhs != 0 && rhs % 32 == 0)
			word--;

		// Adjust index to this word
		rhs -= word * 32;

		// Check it's in bounds
		if (word >= (bitcount/32))
			throw BitIndexOutOfBounds();

		// Return its state
		return (_words[word] & (1 << rhs)) > 0;
	}

	template <int bitcount>
	void Bitset<bitcount>::setBit(unsigned int index)
	{
		// Get word for this bit
		unsigned int word = index / 32;

		if (index != 0 && index % 32 == 0)
			word--;

		// Adjust index to this word
		index -= word * 32;

		// Check it's in bounds
		if (word >= (bitcount/32))
			throw BitIndexOutOfBounds();

		_words[word] |= 1 << index;
	}

	template <int bitcount>
	void Bitset<bitcount>::clearBit(unsigned int index)
	{
		// Get word for this bit
		unsigned int word = index / 32;

		if (index != 0 && index % 32 == 0)
			word--;

		// Adjust index to this word
		index -= word * 32;

		// Check it's in bounds
		if (word >= (bitcount/32))
			throw BitIndexOutOfBounds();

		_words[word] &= ~(1 << index);
	}

	template <int bitcount>
	void Bitset<bitcount>::toggleBit(unsigned int index)
	{
		// Get word for this bit
		unsigned int word = index / 32;

		if (index != 0 && index % 32 == 0)
			word--;

		// Adjust index to this word
		index -= word * 32;

		// Check it's in bounds
		if (word >= (bitcount/32))
			throw BitIndexOutOfBounds();

		_words[word] ^= 1 << index;
	}

	template <int bitcount>
	bool Bitset<bitcount>::isZero() const
	{
		for (uint32_t i = 0; i < (bitcount/32); ++i)
		{
			if (_words[i] != 0)
				return false;
		}

		return true;
	}

	template <int bitcount>
	void Bitset<bitcount>::clear()
	{
		memset(_words, 0, bitcount/8);
	}

	template <int bitcount>
	const uint32_t* Bitset<bitcount>::getData() const
	{
		return _words;
	}
	template <int bitcount>
	uint32_t* Bitset<bitcount>::getData()
	{
		return _words;
	}
	template <int bitcount>
	uint32_t Bitset<bitcount>::getDataSize() const
	{
		return (bitcount/32);
	}

	template <int bitcount>
	class BitsetHash
	{
	public:
		enum
		{
			bucket_size = 4,  // 0 < bucket_size
			min_buckets = 8	  // min_buckets = 2 ^^ N, 0 < N
		};
		size_t operator() (const coment::Bitset<bitcount>& t) const;
		bool operator() (const coment::Bitset<bitcount>& one, const coment::Bitset<bitcount>& two) const;
	};

	template <int bitcount>
	size_t BitsetHash<bitcount>::operator() (const coment::Bitset<bitcount>& t) const
	{
		size_t total = 0;
		for (uint32_t i = 0; i < t.getDataSize(); ++i)
		{
			total += t.getData()[i];
		}
		return total;
	}

	template <int bitcount>
	bool BitsetHash<bitcount>::operator() (const coment::Bitset<bitcount>& one, const coment::Bitset<bitcount>& two) const
	{
		return one == two;
	}
};

#endif /* COMENT_BITSET_H */
