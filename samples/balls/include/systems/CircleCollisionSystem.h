#pragma once

#include "coment/systems/System.h"
#include "coment/util/EntityMap.h"

#include "components/Position.h"
#include "components/Radius.h"

class CircleCollisionSystem
    : public coment::System
{
public:

    /** Initialise the window dimensions & set system priority to 1 (greater than default) */
    CircleCollisionSystem(int width, int height)
        : System(100), mWindowWidth((float)width), mWindowHeight((float)height)
    {
    }

    /* Callbacks */

    /** Allow circles to collide with the edge of the screen */
    void onUpdate() override
    {
        static auto circles = getWorld()->getEntityMap<Position, Radius, Velocity>();

        for (auto& circle : circles)
        {
            // Get components
            Position* pos = circle.getComponent<Position>();
            Velocity* vel = circle.getComponent<Velocity>();
            const Radius* rad = circle.getComponent<Radius>();

            if (pos->x - rad->x < 0)
            {
                pos->x = rad->x;
                vel->x *= -1.0f;
            }
            else if (pos->x + rad->x > mWindowWidth)
            {
                pos->x = mWindowWidth - rad->x;
                vel->x *= -1.0f;
            }

            if (pos->y - rad->x < 0)
            {
                pos->y = rad->x;
                vel->y *= -1.0f;
            }
            else if (pos->y + rad->x > mWindowHeight)
            {
                pos->y = mWindowHeight - rad->x;
                vel->y *= -1.0f;
            }
        }
    }

private:

    /** The width of the window */
    float mWindowWidth;

    /** The height of the window */
    float mWindowHeight;

};