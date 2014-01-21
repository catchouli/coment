#ifndef COMENT_BALLS_RENDERINGSYSTEM_H
#define COMENT_BALLS_RENDERINGSYSTEM_H

#include <iostream>

#include "components/Position.h"
#include "components/Radius.h"
#include "components/Colour.h"

#include "graphics/Drawing.h"

namespace coment
{
        namespace samples
        {
                namespace balls
                {
			class RenderingSystem
				: public coment::EntityProcessingSystem
			{
			public:
				RenderingSystem()
				{

				}

				void registerComponents()
				{
					// Register required components
					registerComponent<Position>();
					registerComponent<Radius>();
					registerComponent<Colour>();
				}

				// Process entities
				virtual void process(const coment::Entity& e)
				{
					// Get properties of circle
					Position* position = _world->getComponent<Position>(e);
					Radius* radius = _world->getComponent<Radius>(e);
					Colour* colour = _world->getComponent<Colour>(e);

					// Draw circle with properties
					Drawing::fillCircle(position->x, position->y, radius->radius, colour->r, colour->g, colour->b);
				}
			};
		}
	}
}

#endif /* COMENT_BALLS_RENDERINGSYSTEM_H */
