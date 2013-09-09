
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
	if (canHoldPlayers())
		m_player = player;
}

const ItemList& Tile::getItems() const
{
	return m_items;
}

void Tile::addItem(const ItemPtr& item)
{
	m_items.push_back(item);
}

