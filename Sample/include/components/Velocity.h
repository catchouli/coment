#ifndef __VELOCITY_H__
#define __VELOCITY_H__

struct Velocity
	: public coment::Component<Velocity>
{
	Velocity()
		: x(0), y(0)
	{

	}

	Velocity(float x, float y)
		: x(x), y(y)
	{

	}

	float x, y;
};

#endif /* __VELOCITY_H__ */
