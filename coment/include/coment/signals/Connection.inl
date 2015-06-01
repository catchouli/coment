#include "coment/signals/Connection.h"
#include "coment/signals/Observer.h"

namespace coment
{
    /** Construct a connection of this type */
    template <typename T, typename... Args>
    Connection_MemberFunctionPointer<T, Args...>::Connection_MemberFunctionPointer(T* objectPtr, PointerType functionPtr, Signal<Args...>* signal)
        : mObjectPtr(objectPtr), mFunctionPtr(functionPtr), mSignal(signal)
    {
        // Ensure observer is derived from Observer
        static_assert(std::is_base_of<Observer, T>::value, "Observer must derive from coment::Observer");
    }

    /** Emit a signal through this connection */
    template <typename T, typename... Args>
    void Connection_MemberFunctionPointer<T, Args...>::emit(Args... args)
    {
        (mObjectPtr->*mFunctionPtr)(args...);
    }

    /** Disconnect this connection from both the signal and the observer */
    template <typename T, typename... Args>
    void Connection_MemberFunctionPointer<T, Args...>::disconnect()
    {
        auto observer = (Observer*)mObjectPtr;
        auto connection = (ConnectionBase*)this;

        // Remove connection from observer
        observer->mConnections.erase(connection);

        // Remove connection from signal
        auto it = mSignal->mConnections.find(connection);
        if (it == mSignal->mConnections.end())
            throw "Internal error (FATAL): Connection not found in signal";

        // This will cause destruction of this connection, so it must be done last
        std::shared_ptr<Connection<Args...>> sharedPtr = it->second;
        mSignal->mConnections.erase(connection);

        auto& obs_connections = mSignal->mObservers.at(observer);
        obs_connections.erase(sharedPtr);

        // If this is the signal's last connection to the observer, remove the observer
        if (obs_connections.size() == 0)
            mSignal->mObservers.erase(observer);
    }
}
