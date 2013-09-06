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

void Player::sendStatusMessage(const std::string& message)
{
	OutputMessage out;
	if (!m_client)
		return;

	out.addByte(NET_MSG_ERROR);
	out.addString(message);
	m_client->send(out);
}

void Player::sendErrorMessage(const std::string& message)
{
	OutputMessage out;
	if (!m_client)
		return;

	out.addByte(NET_MSG_STATUS);
	out.addString(message);
	m_client->send(out);
}

