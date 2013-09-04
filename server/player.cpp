#include "player.h"

Player::Player()
{

}

Player::~Player()
{

}

TilePtr Player::getTile() const
{
	return m_tile;
}

void Player::setTile(const TilePtr& tile)
{
	m_tile = tile;
}

Position2D Player::getPosition() const
{
	return m_tile ? m_tile->getPosition() : Position2D();
}
