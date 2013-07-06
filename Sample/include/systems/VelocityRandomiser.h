#ifndef __VELOCITYRANDOMISER_H__
#define __VELOCITYRANDOMISER_H__

#include <utils/Bag.h>

class VelocityRandomiser
	: public coment::EntityProcessingSystem
{
public:
	void registerComponents()
	{
		// Register required components
		registerComponent<Velocity>();
	}

	void process(coment::Entity e)
	{
		Velocity* velocity = _world->getComponent<Velocity>(e);
		
		velocity->x += (float)(rand() % 10 - 5);
		velocity->y += (float)(rand() % 10 - 3);
	}
};

#endif /* __VELOCITYRANDOMISER_H__ */
