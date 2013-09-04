#ifndef __GAME_H
#define __GAME_H

#include "player.h"

class Game
{
public:
	Game();
	~Game();


private:
	std::list<PlayerPtr> m_players;
};

extern Game g_game;

#endif

