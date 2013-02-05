#ifndef __RENDERINGSYSTEM_H__
#define __RENDERINGSYSTEM_H__

#include "components/Position.h"
#include "components/Radius.h"
#include "components/Colour.h"

class RenderingSystem : public coment::EntityProcessingSystem
{
public:
	RenderingSystem(sf::RenderTarget* target)
		: _target(target)
	{
		// Do other initialisation
		_shape = sf::CircleShape(20.0f, 30);
	}

	void registerComponents()
	{
		// Register required components
		registerComponent<Position>();
		registerComponent<Radius>();
		registerComponent<Colour>();
	}

	// Process entities
	virtual void process(coment::Entity e) 
	{
		// Get properties of circle
		Position* position = _world->getComponent<Position>(e);
		Radius* radius = _world->getComponent<Radius>(e);
		Colour* colour = _world->getComponent<Colour>(e);

		// Draw circle with properties
		_shape.setPosition(position->x, position->y);
		_shape.setFillColor(*colour);
		_shape.setRadius(radius->radius);
		_shape.setOrigin(radius->radius, radius->radius);
		_target->draw(_shape);
	}

private:
	sf::RenderTarget* _target;
	sf::CircleShape _shape;
};

#endif /* __RENDERINGSYSTEM_H__ */
