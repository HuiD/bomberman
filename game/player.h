#ifndef __PLAYER_H
#define __PLAYER_H

#include "../net/protocolgame.h"

#include "decl.h"
#include "tile.h"

class Player
{
public:
	Player();
	~Player();

	TilePtr getTile() const;
	void setTile(const TilePtr& tile);

	Position2D getPosition() const;

	uint32_t getID() const { return m_id; }
	void setID(uint32_t id) { m_id = id; }

	ProtocolGamePtr getClient() const { return m_client; }
	void setClient(const ProtocolGamePtr& client) { m_client = client; }

	void sendStatusMessage(const std::string& message);
	void sendErrorMessage(const std::string& message);

private:
	uint32_t m_id;

	ProtocolGamePtr m_client;
	TilePtr m_tile;
};

#endif

