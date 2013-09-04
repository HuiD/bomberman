#include "tile.h"
#include "item.h"

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
	if (m_player)
		return false;

	for (const ItemPtr& i : m_items)
		if (i->blocksPath())
			return false;
	return true;
}


