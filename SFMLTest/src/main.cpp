#include <World.h>
#include <systems/EntityProcessingSystem.h>

#define SFML_STATIC
#include <SFML/Graphics.hpp>

struct RenderComponent : public coment::Component<RenderComponent>
{
	RenderComponent()
		: color(rand() % 255, rand() % 255, rand() % 255, 255)
	{

	}

	sf::Color color;
};

struct MoveComponent : public coment::Component<MoveComponent>
{
	MoveComponent()
	{
		x = 200;
		y = 200;
		xVel = (-1 + 2 * (rand() / (float)RAND_MAX)) * 100.0f;
		yVel = (-1 + 2 * (rand() / (float)RAND_MAX)) * 100.0f;
		radius = 10.0f + (rand() / (float)RAND_MAX) * 20.0f;
	}

	float x, y;
	float xVel, yVel;
	float radius;
};

class RenderSystem : public coment::EntityProcessingSystem
{
public:
	RenderSystem(sf::RenderTarget* target)
	{
		// Register
		registerComponent<MoveComponent>();
		registerComponent<RenderComponent>();

		_target = target;
		_shape = sf::CircleShape(20.0f, 30);

	}

	virtual ~RenderSystem() 
	{

	}

	// Process each entity.
	virtual void process(coment::Entity e) 
	{
		RenderComponent* render = _world->getComponent<RenderComponent>(e);
		MoveComponent* move = _world->getComponent<MoveComponent>(e);
		_shape.setPosition(move->x, move->y);
		_shape.setFillColor(render->color);
		_shape.setRadius(move->radius);
		_shape.setOrigin(move->radius, move->radius);
		_target->draw(_shape);
	}

private:
	sf::RenderTarget* _target;
	sf::CircleShape _shape;
};

class MoveSystem : public coment::EntityProcessingSystem
{
public:
	MoveSystem(float width, float height)
	{
		// Register
		registerComponent<MoveComponent>();

		_width = width;
		_height = height;
	}

	virtual ~MoveSystem()
	{

	}

	// Process
	virtual void process(coment::Entity e)
	{
		MoveComponent* move = _world->getComponent<MoveComponent>(e);
		move->x += move->xVel * _world->getDelta();
		move->y += move->yVel * _world->getDelta();

		// If we hit a wall, then bounce.
		if ((move->x - move->radius < 0 && move->xVel < 0) || (move->x + move->radius > _width && move->xVel > 0)) 
			move->xVel = -move->xVel;
		if ((move->y - move->radius < 0 && move->yVel < 0) || (move->y + move->radius > _height && move->yVel > 0))
			move->yVel = -move->yVel;
	}

private:
	float _width, _height;
};

struct FakeComponent
	: public coment::Component<FakeComponent>
{

};

int main(int argc, char** argv) 
{
	// Create world.
	coment::World world;

	coment::Entity e = world.createEntity();
	world.addComponent(e, FakeComponent());

	sf::RenderWindow window(sf::VideoMode(800, 600), "Coment SFML Test");
	window.setVisible(true);

	// Create some systems.
	RenderSystem render(&window);
	MoveSystem mover((float)window.getSize().x, (float)window.getSize().y);

	// Add these systems to the world.
	world.registerSystem(render);
	world.registerSystem(mover);

	int numBalls = 0;

	// Add some balls.
	for (int i = 0; i < 1000; ++i)
	{
		coment::Entity e = world.createEntity();
		world.addComponent(e, MoveComponent());
		world.addComponent(e, RenderComponent());
		world.refresh(e);
		numBalls++;
	}

	// Create a clock.
	sf::Clock clock;

	// Whether or not to draw
	bool draw = true;

	// Update the window.
	while (window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					coment::Entity e = world.createEntity();
					world.addComponent(e, MoveComponent());
					world.addComponent(e, RenderComponent());
					world.refresh(e);

					numBalls++;
				}
				if (event.key.code == sf::Keyboard::D)
				{
					draw = !draw;
				}
			}
		}

		window.clear(sf::Color(255, 255, 255, 255));

		// Begin loop
		world.loopStart();
		world.setDelta(clock.restart().asSeconds());

		// Process systems
		mover.update();

		if (draw)
			render.update();

		// Render window
		window.display();

		// Update title
		char buf[1024];
		sprintf_s(buf, "%i Balls, %f FPS", numBalls, 1.0f / world.getDelta());
		window.setTitle(buf);
	}

	return 0;
}
