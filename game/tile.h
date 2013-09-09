#ifndef __TILE_H
#define __TILE_H

#include "decl.h"

class Tile
{
public:
	Tile(const Position2D& pos);
	~Tile();

	Position2D getPosition() const;

	PlayerPtr getPlayer() const;
	void setPlayer(const PlayerPtr& player);

	const ItemList& getItems() const;
	void addItem(const ItemPtr& item);

	bool canHoldPlayers() const { return m_canHoldPlayers; }
	void setCanHoldPlayers(bool hold) { m_canHoldPlayers = hold; }

private:
	bool m_canHoldPlayers;
	Position2D m_position;
	PlayerPtr m_player;
	ItemList m_items;
};

#endif

