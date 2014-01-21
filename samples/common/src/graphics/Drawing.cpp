#include "graphics/Drawing.h"

#include <math.h>
#include <SDL2/SDL_opengl.h>

namespace coment
{
	namespace samples
	{
		void Drawing::fillCircle(float x, float y, float radius, float r, float g, float b)
		{
			static bool generated = false;
			static GLfloat vertices[(CIRCLE_SUBDIVISIONS + 2) * 3];

			// Set colour
			glColor3f(r, g, b);

			// Translate to x, y
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glTranslatef(x, y, 0.0f);
			glScalef(radius, radius, 1.0f);

			// Generate if not generated
			if (!generated)
			{
				if (CIRCLE_SUBDIVISIONS <= 2)
					return;

				// Calculate rotation step
				double step = (2.0 * M_PI) / (double)CIRCLE_SUBDIVISIONS;

				// Store centre at start of vertices
				GLfloat* start = vertices;
				start[0] = 0.0f;
				start[1] = 0.0f;
				start[2] = 0.0f;

				// Calculate outer vertices
				for (int i = 0; i < CIRCLE_SUBDIVISIONS; ++i)
				{
					double angle = step * i;
					GLfloat* vertex = &vertices[(i + 1) * 3];
					vertex[0] = (float)(1.0f * sin(angle));
					vertex[1] = (float)(1.0f * cos(angle));
					vertex[2] = 0.0f;
				}

				// Close off the circle
				GLfloat* last = vertices + (CIRCLE_SUBDIVISIONS + 1) * 3;
				last[0] = start[3];
				last[1] = start[4];
				last[2] = start[5];

				// Store generated status
				generated = true;
			}

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, vertices);

			glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_SUBDIVISIONS + 2);

			glDisableClientState(GL_VERTEX_ARRAY);

			glPopMatrix();
		}
	}
}
