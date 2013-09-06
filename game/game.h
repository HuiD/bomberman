#ifndef __GAME_H
#define __GAME_H

#include "player.h"

#define MAX_GAME_PLAYERS 4 	// maximum players in the game
#define MIN_GAME_PLAYERS 2 	// minimum requirement to start the game
#define PING_DELAY 60000  	// in milliseconds
#define SECONDS_TO_START_GAME 3

class Game
{
public:
	Game();
	~Game();

	PlayerPtr getPlayer(uint32_t playerId);

	void processPlayerMove(uint32_t playerId, const Position2D& movePos);
	void processPlayerConnect(uint32_t playerId, const ProtocolGamePtr& c);
	void processPlayerDisconnect(uint32_t playerId);
	void processGameStart(uint32_t playerId);
	void processGameCancelStart(uint32_t playerId);

protected:
	void start();
	void ping(const PlayerPtr& player);

private:
	uint32_t m_startEvent;

	std::list<PlayerPtr> m_players;
	std::list<struct PingHandler> m_pingHandlers;
};

#endif

