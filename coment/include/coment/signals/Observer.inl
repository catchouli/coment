#include "coment/signals/Observer.h"
#include "coment/signals/Connection.h"

namespace coment
{
    inline Observer::~Observer()
    {
        // Copy list so it can be modified
        auto connections = mConnections;

        // Disconnect all connections
        for (auto& connection : connections)
        {
            connection->disconnect();
        }
    }
}