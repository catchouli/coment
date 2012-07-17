#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <World.h>

#include <systems/EntityProcessingSystem.h>

using namespace coment;

struct Health
	: public Component<Health>
{
	Health()
	{

	}

	Health(int value)
	{
		this->value = value;
	}

	int value;
};

struct Position
	: public Component<Position>
{
	Position()
	{

	}


	Position(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	int x, y;
};

class HealthSystem
	: public EntityProcessingSystem
{
public:
	HealthSystem()
	{
		registerComponent<Health>();
	}

	void process(Entity e)
	{

	}
};

class HealthPosSystem
	: public EntityProcessingSystem
{
public:
	HealthPosSystem()
	{
		registerComponent<Health>();
		registerComponent<Position>();
	}

	void process(Entity e)
	{

	}
};

int main(int argc, char** argv)
{
	World world;
	HealthSystem healthSystem;
	HealthPosSystem healthPosSystem;
	
	world.registerSystem(healthSystem);
	world.registerSystem(healthPosSystem);

	Health health(100);
	Position pos(50, 50);

	GroupManager& groups = world.getGroupManager();
	
	for (int i = 0; i < 1000; ++i)
	{
		Entity e = world.createEntity();

		if (i % 2 == 0)
		{
			groups.set("even", e);
			world.addComponent(e, health);
		}
		else
		{
			groups.set("odd", e);
		}

		health.value = i;
		
		world.addComponent(e, pos);
		world.refresh(e);
	}

	for (int i = 0; i < 300; ++i)
	{
		world.remove(*(Entity*)&i);
	}

	for (int i = 0; i < 300; ++i)
	{
		world.createEntity();
	}

	// While stroustrup is crying
	for (;;)
	{
		// Begin loop
		world.loopStart();
		world.setDelta(0);

		// Process systems
		healthSystem.update();
		healthPosSystem.update();
	}

 	return 0;
}
