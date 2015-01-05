#pragma once

#include <coment/Component.h>

struct Radius
    : public coment::Component
{
    Radius(float x = 0.0f) : x(x) {}

    float x;
};