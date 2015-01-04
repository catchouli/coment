#pragma once

// This allows our type to access the private members of dynamic_bitset
// As a result, this header must be included before or instead of the real dynamic_bitset
// headers, or before any other headers that might include it
#include <boost/dynamic_bitset/config.hpp>
#undef BOOST_DYNAMIC_BITSET_PRIVATE
#define BOOST_DYNAMIC_BITSET_PRIVATE public
#include <boost/dynamic_bitset.hpp>

#include "coment/util/combined_hash.h"

namespace coment
{
    template <typename Block = unsigned long,
        typename Allocator = std::allocator<Block>>
    class dynamic_bitset
        : public boost::dynamic_bitset<Block, Allocator>
    {
    public:

        /** Generate a hash from this dynamic_bitset */
        size_t hash() const;

        /** Check if this bitset is equal to another bitset */
        bool operator==(const dynamic_bitset<Block, Allocator>& other);

        /** Check if this bitset is not equal to another bitset */
        bool operator!=(const dynamic_bitset<Block, Allocator>& other);

        /** Check if this bitset is a subset of a */
        bool is_subset_of(const dynamic_bitset<Block, Allocator>& a) const;

    };

    /** Hash function for bitsets */
    template <typename Block, typename Allocator>
    size_t dynamic_bitset<Block, Allocator>::hash() const
    {
        size_t hash = 0;
        size_t cumulative_hash = 0;

        // Create hash from block hashes
        for (auto& block : m_bits)
        {
            hash_combine(cumulative_hash, block);

            // If current block is non-zero, copy cumulative_hash to hash
            // to signify it is okay to return. This is done so that bitmasks
            // of different lengths can be compared [they will be equal with trailing zeros]
            if (block != 0)
                hash = cumulative_hash;
        }

        return hash;
    }

    /** Check if this bitset is equal to another bitset */
    template <typename Block, typename Allocator>
    bool dynamic_bitset<Block, Allocator>::operator==
        (const dynamic_bitset<Block, Allocator>& other)
    {
        const dynamic_bitset<Block, Allocator>* shortest;
        const dynamic_bitset<Block, Allocator>* longest;

        size_t shortestBlockLen;
        size_t longestBlockLen;

        // Order bitsets
        if (m_bits.size() <= other.m_bits.size())
        {
            shortest = this;
            longest = &other;

            shortestBlockLen = m_bits.size();
            longestBlockLen = other.m_bits.size();
        }
        else
        {
            shortest = &other;
            longest = this;

            shortestBlockLen = other.m_bits.size();
            longestBlockLen = m_bits.size();
        }

        // Compare up to guaranteed (shortest) length
        for (unsigned int i = 0; i < shortestBlockLen; ++i)
        {
            const auto& a = m_bits[i];
            const auto& b = other.m_bits[i];

            if (a != b)
                return false;
        }

        // Check that the remaining bits on the longer bitset is zero
        for (unsigned int i = shortestBlockLen; i < longestBlockLen; ++i)
        {
            const auto& a = longest->m_bits[i];

            if (a != 0)
                return false;
        }

        return true;
    }

    /** Check if this bitset is not equal to another bitset */
    template <typename Block, typename Allocator>
    bool dynamic_bitset<Block, Allocator>::operator!=
        (const dynamic_bitset<Block, Allocator>& other)
    {
        return !(*this == other);
    }

    /** Check if this bitset is a subset of a */
    template <typename Block, typename Allocator>
    bool dynamic_bitset<Block, Allocator>::
        is_subset_of(const dynamic_bitset<Block, Allocator>& a) const
    {
        size_t fewestBlocks = std::min(num_blocks(), a.num_blocks());

        // Default check - check up to common length
        for (size_type i = 0; i < fewestBlocks; ++i)
            if (m_bits[i] & ~a.m_bits[i])
                return false;

        // Check the rest of this is all zero if it's longer,
        // or it might still not be a subset
        if (num_blocks() > a.num_blocks())
        {
            for (size_t i = a.num_blocks(); i < num_blocks(); ++i)
            {
                const auto& block = m_bits[i];

                if (block != 0)
                    return false;
            }
        }

        return true;
    }

}

// Hash specialisation
namespace std
{

    template <>
    struct hash<coment::dynamic_bitset<>>
    {
        size_t operator()(const coment::dynamic_bitset<>& x) const
        {
            return x.hash();
        }
    };

}