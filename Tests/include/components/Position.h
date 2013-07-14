#ifndef __POSITION_H__
#define __POSITION_H__

namespace coment
{
        namespace tests
        {
		struct Position
			: public coment::Component
		{
			Position()
				: x(0), y(0)
			{

			}

			int x, y;
		};
	}
}

#endif /* __POSITION_H__ */
