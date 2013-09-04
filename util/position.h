#ifndef __POSITION_H
#define __POSITION_H

class Position2D
{
public:
	uint16_t x, y;

	Position2D(uint16_t _x, uint16_t _y) :
		x(_x,) ,y(_y)
	{
	}

	Position2D(const Position2D& p) :
		x(p.x), y(p.y)
	{
	}

	Position2D& operator=(const Position2D& p)
	{
		x = p.x;
		y = p.y;
	}

	bool operator==(const Position2D& p) const
	{
		return x == p.x && y == p.y;
	}
	bool operator!=(const Position2D& p) const
	{
		return x != p.x && y != p.y;
	}
	bool operator<(const Position2D& p) const
	{
		return x < p.x && y < p.y;
	}
};

#endif

