#pragma once

#include <coment/Component.h>

struct Color
    : public coment::Component
{
    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f) : r(r), g(g), b(b) {}

    float r, g, b;
};