#ifndef __POSITION_H__
#define __POSITION_H__

struct Position
	: public coment::Component<Position>
{
	Position()
		: x(0), y(0)
	{

	}

	Position(float x, float y)
		: x(x), y(y)
	{
		
	}

	float x, y;
};

#endif /* __POSITION_H__ */
