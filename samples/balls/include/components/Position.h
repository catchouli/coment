#pragma once

#include <coment/Component.h>

struct Position
    : public coment::Component
{
    Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    float x, y;
};