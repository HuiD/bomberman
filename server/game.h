#ifndef __GAME_H
#define __GAME_H

#include "player.h"

#define MAX_GAME_PLAYERS 4
#define MIN_GAME_PLAYERS 2

class Game
{
public:
	Game();
	~Game();

	PlayerPtr getPlayer(uint32_t playerId);

	void processPlayerMove(uint32_t playerId, const Position2D& movePos);
	void processPlayerConnect(uint32_t playerId);
	void processPlayerDisconnect(uint32_t playerId);

private:
	std::array<PlayerPtr, MAX_GAME_PLAYERS> m_players;
};

extern Game g_game;

#endif

