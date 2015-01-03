#pragma once

#include <functional>

namespace coment
{

    /** Combine hash in seed with hash of t1 */
    template <typename T1>
    void hash_combine(size_t& seed, const T1& t1)
    {
        // Combine hashes
        seed ^= std::hash<T1>()(t1) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    /** Combine hash in seed with hashes in t1, t2, args... */
    template <typename T1, typename T2, typename... Ts>
    void hash_combine(size_t& seed, const T1& t1, const T2& t2, const Ts&... args)
    {
        // Process t1 and then the rest of the argument pack
        hash_combine(seed, t1);
        hash_combine(seed, t2, args...);
    }

    /** Calculate a combined hash from args */
    template <typename... Args>
    size_t combined_hash(const Args&... args)
    {
        size_t hash = 0;

        hash_combine(hash, args...);

        return std::move(hash);
    }

}