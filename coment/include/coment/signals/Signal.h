#pragma once

#include "coment/signals/Connection.h"

#include <unordered_set>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <type_traits>

namespace coment
{
    class Observer;

    /** The signal class. Allows observers to be connected and disconnected, and signals to be emitted.
        Types of call arguments for emit should be provided in Args */
    template <typename... Args>
    class Signal
    {
    public:

        /** The type of connections this Signal holds */
        typedef Connection<Args...> ConnectionType;

        /** Disconnect signal when it goes out of scope */
        ~Signal();

        /** Connect a signal to an observer */
        template <typename T>
        void connect(T* objectPtr, typename Connection_MemberFunctionPointer<T, Args...>::PointerType fp);

        /** Disconnect a signal from an observer */
        template <typename T>
        void disconnect(T* objectPtr);

        /** Disconnect all observers */
        void disconnectAll();

        /** Emit a signal */
        void emit(Args... args);

    private:

        // This is bad, but the purpose of this library is to prevent things like this :3
        template <typename T, typename... Args>
        friend class Connection_MemberFunctionPointer;

        /** The observers connected to this signal, and their connections */
        std::unordered_map<Observer*, std::unordered_set<std::shared_ptr<ConnectionType>>> mObservers;

        /** A map of connection base pointers to shared pointers, used for cleaning up */
        std::unordered_map<ConnectionBase*, std::shared_ptr<ConnectionType>> mConnections;

    };

}

#include "coment/signals/Signal.inl"