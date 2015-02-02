#include "coment/signals/Signal.h"
#include "coment/signals/Observer.h"

namespace coment
{
    /** Disconnect signal when it goes out of scope */
    template <typename... Args>
    Signal<Args...>::~Signal()
    {
        disconnectAll();
    }

    /** Connect a signal to an observer */
    template <typename... Args>
    template <typename T>
    void Signal<Args...>::connect(T* objectPtr, typename Connection_MemberFunctionPointer<T, Args...>::PointerType fp)
    {
        // Ensure observer is derived from Observer
        static_assert(std::is_base_of<Observer, T>::value, "Observer must derive from coment::Observer");

        // Cast observer pointer to Observer*
        auto observer = (Observer*)objectPtr;

        // Create connection
        auto sharedPtr = std::make_shared<Connection_MemberFunctionPointer<T, Args...>>(objectPtr, fp, this);

        // Notify observer of connection
        observer->mConnections.insert(sharedPtr.get());

        // Store connection
        mConnections[(ConnectionBase*)sharedPtr.get()] = sharedPtr;
        mObservers[observer].insert(sharedPtr);
    }

    /** Disconnect a signal from an observer */
    template <typename... Args>
    template <typename T>
    void Signal<Args...>::disconnect(T* objectPtr)
    {
        // Ensure observer is derived from Observer
        static_assert(std::is_base_of<Observer, T>::value, "Observer must derive from coment::Observer");

        // Cast observer pointer to Observer*
        auto observer = (Observer*)objectPtr;

        // Copy map so we can modify the old one
        auto map = mObservers;

        // Remove connections
        for (auto& connection : map.at(observer))
        {
            connection->disconnect();
        }
    }

    /** Disconnect all observers */
    template <typename... Args>
    void Signal<Args...>::disconnectAll()
    {
        // Copy map so we can modify the old one
        auto observers = mObservers;

        // Remove connections
        for (auto& observer : observers)
        {
            for (auto& connection : observer.second)
            {
                connection->disconnect();
            }
        }
    }

    /** Emit a signal */
    template <typename... Args>
    void Signal<Args...>::emit(Args... args)
    {
        // For each observer
        for (auto& observer : mObservers)
        {
            // For each observer's connection
            for (auto& connection : observer.second)
            {
                // Emit the signal
                connection->emit(args...);
            }
        }
    }
}