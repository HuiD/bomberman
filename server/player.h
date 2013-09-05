#ifndef __PLAYER_H
#define __PLAYER_H

#include "../net/connection.h"

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

	ConnectionPtr getConnection() const { return m_conn; }
	void setConnection(const ConnectionPtr& conn) { m_conn = conn; }

private:
	uint32_t m_id;

	ConnectionPtr m_conn;
	TilePtr m_tile;
};

#endif

