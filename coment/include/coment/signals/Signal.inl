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

    /* SignalBase proxies for type erasure */

    /** Check two types are the same and throw an exception otherwise */
    inline void checkTypes(std::type_index A, std::type_index B)
    {
        if (A != B)
        {
            throw std::exception("Wrong Args... specified for this signal");
        }
    }
    
    /** Connect a signal to an observer */
    template <typename... Args, typename T>
    void SignalBase::connect(T* objectPtr, typename Connection_MemberFunctionPointer<T, Args...>::PointerType fp)
    {
        // Check signal type
        checkTypes(typeid(Signal<Args...>), mType);

        // Get signal pointer
        auto signal = (Signal<Args...>*)this;

        // Connect signal
        signal->connect(objectPtr, fp);
    }

    /** Disconnect a signal from an observer */
    template <typename... Args, typename T>
    void SignalBase::disconnect(T* objectPtr)
    {
        // Check signal type
        checkTypes(typeid(Signal<Args...>), mType);

        // Get signal pointer
        auto signal = (Signal<Args...>*)this;

        // Connect signal
        signal->disconnect(objectPtr);
    }

    /** Disconnect all observers */
    template <typename... Args>
    void SignalBase::disconnectAll()
    {
        // Check signal type
        checkTypes(typeid(Signal<Args...>), mType);

        // Get signal pointer
        auto signal = (Signal<Args...>*)this;

        // Connect signal
        signal->disconnectAll();
    }

    /** Emit a signal */
    template <typename... Args>
    void SignalBase::emit(Args... args)
    {
        // Check signal type
        checkTypes(typeid(Signal<Args...>), mType);

        // Get signal pointer
        auto signal = (Signal<Args...>*)this;

        // Connect signal
        signal->emit(args...);
    }
}