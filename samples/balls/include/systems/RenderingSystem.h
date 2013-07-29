#ifndef COMENT_BALLS_RENDERINGSYSTEM_H
#define COMENT_BALLS_RENDERINGSYSTEM_H

#include "components/Position.h"
#include "components/Radius.h"
#include "components/Colour.h"

#include "graphics/PixelBuffer.h"

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
				RenderingSystem(PixelBuffer* target)
					: _target(target)
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
					_target->drawCircle(colour->colour, radius->radius, position->x, position->y);
				}

			private:
				PixelBuffer* _target;
			};
		}
	}
}

#endif /* COMENT_BALLS_RENDERINGSYSTEM_H */
