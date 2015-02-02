#pragma once

namespace coment
{
    template <typename... Args>
    class Signal;

    /** The base class for connections */
    class ConnectionBase
    {
    public:

        /** Allow derived types to be cleaned up through a pointer to ConnectionBase */
        virtual ~ConnectionBase() {};

        /** Disconnect this connection from both the signal and the observer */
        virtual void disconnect() = 0;

    };

    /** The base class for connections with specific arguments */
    template <typename... Args>
    class Connection
        : public ConnectionBase
    {
    public:

        /** Allow derived types to be cleaned up through a pointer to Connection */
        virtual ~Connection() {};

        /** Emit a signal through this connection */
        virtual void emit(Args... args) = 0;

        /** Disconnect this connection from both the signal and the observer */
        virtual void disconnect() override = 0;

    };

    /** A connection to a member function */
    template <typename T, typename... Args>
    class Connection_MemberFunctionPointer
        : public Connection<Args...>
    {
    public:

        typedef void (T::*PointerType)(Args...);

        /** Construct a connection of this type */
        Connection_MemberFunctionPointer(T* objectPtr, PointerType functionPtr, Signal<Args...>* signal);

        /** Emit a signal through this connection */
        void emit(Args... args) override;

        /** Disconnect this connection from both the signal and the observer */
        void disconnect() override;

    private:

        /** A pointer to the observer */
        T* mObjectPtr;

        /** A pointer to the member function */
        PointerType mFunctionPtr;

        /** A pointer to the signal (for cleanup) */
        Signal<Args...>* mSignal;

    };

}

#include "coment/signals/Connection.inl"