#pragma once

namespace coment
{
    template <typename T>
    struct PriorityComparator
    {
        bool operator()(const T* lhs, const T* rhs)
        {
            return lhs->getPriority() > rhs->getPriority();
        }
    };
}