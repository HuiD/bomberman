#ifndef __POSITION_H
#define __POSITION_H

#include <stdint.h>

class Position2D
{
public:
	uint16_t x, y;

	Position2D(uint16_t _x, uint16_t _y) :
		x(_x), y(_y)
	{
	}
	Position2D()
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
		return *this;
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
	bool isValid() const { return x != 0 && y != 0; }
};

inline std::ostream& operator<<(std::ostream& os, const Position2D& pos)
{
	os << "Position2D(" << pos.x << ", " << pos.y << ")";
	return os;
}

#endif

