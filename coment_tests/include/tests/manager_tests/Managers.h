#pragma once

#include <coment/Entity.h>
#include <coment/managers/Manager.h>

class DefaultManager
    : public coment::Manager<DefaultManager>
{

};

class CallbackTestManager
    : public coment::Manager<CallbackTestManager>
{
public:

    /* Callbacks */

    /** Called when an entity is added to the manager */
    void onEntityAdded(const coment::Entity& e) override
    {
        onEntityAddedCalls++;
    }

    /** Called when an entity is removed from the manager */
    void onEntityRemoved(const coment::Entity& e) override
    {
        onEntityRemovedCalls++;
    }

    /** Called before the world is updated */
    void preUpdate() override
    {
        preUpdateCalls++;
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
    int postUpdateCalls = 0;

};