#ifndef __RADIUS_H__
#define __RADIUS_H__

struct Radius
	: public coment::Component<Radius>
{
	Radius()
		: radius(0)
	{

	}

	Radius(float radius)
		: radius(radius)
	{

	}

	float radius;
};

#endif /* __RADIUS_H__ */
