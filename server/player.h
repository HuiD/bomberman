#ifndef __PLAYER_H
#define __PLAYER_H

#include "tile.h"
#include "decl.h"

class Player
{
public:
	Player();
	~Player();

	TilePtr getTile() const;
	void setTile(const TilePtr& tile);

private:
	TilePtr m_tile;
};

#endif

