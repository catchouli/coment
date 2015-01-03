#pragma once

// This allows our type to access the private members of dynamic_bitset
// As a result, this header must be included before or instead of the real dynamic_bitset
// headers, or before any other headers that might include it
#include <boost/dynamic_bitset/config.hpp>
#undef BOOST_DYNAMIC_BITSET_PRIVATE
#define BOOST_DYNAMIC_BITSET_PRIVATE public
#include <boost/dynamic_bitset.hpp>

#include "combined_hash.h"

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

    };

    template <typename Block, typename Allocator>
    size_t dynamic_bitset<Block, Allocator>::hash() const
    {
        size_t hash = 0;

        // Create hash from block hashes
        for (auto& block : m_bits)
        {
            hash_combine(hash, block);
        }

        return hash;
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