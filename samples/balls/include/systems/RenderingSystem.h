#pragma once

#include "coment/systems/System.h"
#include "coment/util/EntityMap.h"

#include "components/Position.h"
#include "components/Radius.h"
#include "components/Color.h"

#include <vector>

struct Vertex
{
    float x, y;
};

std::vector<Vertex> createCircleVertexArray(int circleVertexCount);

class RenderingSystem
    : public coment::System<RenderingSystem>
{
public:

    /** Initialises the vertex array & initialise priority to 1000 so it runs after updates */
    RenderingSystem(int width, int height, int circleVertexCount = 32)
        : System(1000), mWindowWidth(width), mWindowHeight(height)
    {
        // Initialise vertex array
        mCircleVertexArray = createCircleVertexArray(circleVertexCount);
    }

    /* Callbacks */

    /** Clear screen before update */
    void preUpdate() override
    {
        // Clear screen
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set up view
        glViewport(0, 0, mWindowWidth, mWindowHeight);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, static_cast<double>(mWindowWidth), 0.0, static_cast<double>(mWindowHeight), 0.0f, 1.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    /** Render circles on update */
    void onUpdate() override
    {
        // Map of circles
        static auto mCircles = getWorld()->getEntityMap<Position, Radius>();

        // Draw circles
        for (auto& circle : mCircles)
        {
            const Color defaultColor(0.0f, 0.0f, 0.0f);

            // Get components
            const Position* position = circle.getComponent<Position>();
            const Radius* radius = circle.getComponent<Radius>();
            const Color* color = circle.getComponent<Color>();

            if (color == nullptr)
                color = &defaultColor;

            // Set colour
            glColor3f(color->r, color->g, color->b);

            // Move circle to position and scale it to radius
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(position->x, position->y, 0.0f);
            glScalef(radius->x, radius->x, 1.0f);

            // Enable vertex arrays
            glEnableClientState(GL_VERTEX_ARRAY);

            // Set vertex array pointer
            glVertexPointer(2, GL_FLOAT, 0, mCircleVertexArray.data());

            // Draw circle
            glDrawArrays(GL_TRIANGLE_FAN, 0, mCircleVertexArray.size());
        }
    }

private:

    /** The vertex array for the circle */
    std::vector<Vertex> mCircleVertexArray;

    /** The width of the window we're rendering to */
    int mWindowWidth;

    /** The height of the window we're rendering to */
    int mWindowHeight;

};

inline std::vector<Vertex> createCircleVertexArray(int circleVertexCount)
{
    std::vector<Vertex> circleVertexArray;

    if (circleVertexCount <= 6)
        throw std::invalid_argument("Circle vertex count must be greater than 6");

    // Resize vertex array
    circleVertexArray.resize(circleVertexCount);

    // Create circle vertex buffer with r = 1 centred at (0, 0)
    circleVertexArray[0] = { 0.0f, 0.0f };

    // 2 vertices are reserved for the start and end point
    for (int i = 0; i < circleVertexCount - 2; ++i)
    {
        // How far we are around the circle in radians
        double angle = 2.0 * M_PI * (i / circleVertexCount - 2);

        // Set the circle's vertices
        circleVertexArray[i] = { static_cast<float>(sin(angle)), static_cast<float>(cos(angle)) };
    }

    // The final vertex should loop back around
    circleVertexArray[circleVertexCount - 1] = circleVertexArray[1];

    return circleVertexArray;
}