#pragma once

#include <coment/Entity.h>
#include <coment/systems/System.h>

class CallbackTestSystem
    : public coment::System
{
public:

    /* Callbacks */

    /** Called when an entity is added to the system */
    void onEntityAdded(const coment::Entity& e) override
    {
        onEntityAddedCalls++;
    }

    /** Called when an entity is removed from the system */
    void onEntityRemoved(const coment::Entity& e) override
    {
        onEntityRemovedCalls++;
    }

    /** Called before the world is updated */
    void preUpdate() override
    {
        preUpdateCalls++;
    }

    /** Called while the world is updated */
    void onUpdate() override
    {
        onUpdateCalls++;
    }

    /** Called after the world is updated */
    void postUpdate() override
    {
        postUpdateCalls++;
    }

    /* Counters for callback calls */
    int onEntityAddedCalls = 0;
    int onEntityRemovedCalls = 0;
    int preUpdateCalls = 0;
    int onUpdateCalls = 0;
    int postUpdateCalls = 0;

};