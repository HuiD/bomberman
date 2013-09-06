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

	ItemList getItems() const;
	void addItem(const ItemPtr& item);

	bool canAdd(const PlayerPtr& player) const;

private:
	Position2D m_position;
	PlayerPtr m_player;
	ItemList m_items;
};

#endif

