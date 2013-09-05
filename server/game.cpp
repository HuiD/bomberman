#include "game.h"

#include "../net/outputmessage.h"

Game g_game;

Game::Game()
{

}

Game::~Game()
{

}

PlayerPtr Game::getPlayer(uint32_t playerId)
{
	for (uint i = 0; i < MAX_GAME_PLAYERS; ++i)
		if (m_players[i]->getID() == playerId)
			return m_players[i];
	return nullptr;
}

void Game::processPlayerMove(uint32_t playerId, const Position2D& movePos)
{
	PlayerPtr player = getPlayer(playerId);
	if (!player)
		return;

	OutputMessage out;
	ConnectionPtr conn = player->getConnection();
	if (!conn)
		return;
}

void Game::processPlayerConnect(uint32_t playerId)
{
	PlayerPtr newPlayer(new Player);

	newPlayer->setID(playerId);
}

void Game::processPlayerDisconnect(uint32_t playerId)
{

}

