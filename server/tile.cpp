
#include "tile.h"
#include "item.h"
#include "player.h"

Tile::Tile(const Position2D& pos) :
	m_position(pos)
{

}

Tile::~Tile()
{
	m_player = nullptr;
	m_items.clear();
}

Position2D Tile::getPosition() const
{
	return m_position;
}

PlayerPtr Tile::getPlayer() const
{
	return m_player;
}

void Tile::setPlayer(const PlayerPtr& player)
{
	if (canAdd(player))
		m_player = player;
}

ItemList Tile::getItems() const
{
	return m_items;
}

void Tile::addItem(const ItemPtr& item)
{
	m_items.push_back(item);
}

bool Tile::canAdd(const PlayerPtr& player) const
{
	// If there's already a player on this, don't do anything.
	// We can't stack up 2 players on the same tile.
	if (m_player)
		return false;

	for (const ItemPtr& i : m_items)
		if (i->blocksPath())
			return false;
	return true;
}


