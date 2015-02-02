#pragma once

#include <unordered_set>

namespace coment
{
    class ConnectionBase;

    /** The base class for observers. Observers wishing to be connected to signals
        will need to inherit from this class, which will then provide cleanup for connections. */
    class Observer
    {
    public:

        virtual ~Observer();

    private:

        // This is bad, but the purpose of this library is to prevent things like this :3
        template <typename T, typename... Args>
        friend class Connection_MemberFunctionPointer;
        
        template <typename... Args>
        friend class Signal;

        /** The connections connected to this observer */
        std::unordered_set<ConnectionBase*> mConnections;

    };
}

#include "coment/signals/Observer.inl"