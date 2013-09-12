/*
 * Copyright (c) 2013 Ahmed Samy  <f.fallen45@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "game.h"

#include "../net/outputmessage.h"

struct PingHandler
{
	PlayerPtr player;
	uint32_t pingEvent;

	void start()
	{
		pingEvent = g_sched.scheduleEvent(std::bind(&PingHandler::ping, this), PING_DELAY, true);
	}

	void stop()
	{
		g_sched.stopEvent(pingEvent);
	}

	void ping()
	{
		if (!player) {
			g_sched.stopEvent(pingEvent);
			return;
		}

		ProtocolGamePtr c = player->getClient();
		if (!c) {
			g_sched.stopEvent(pingEvent);
			return;
		}

		c->sendPing();
	}
};

Game::Game()
{

}

Game::~Game()
{

}

PlayerPtr Game::getPlayer(uint32_t playerId)
{
	for (const PlayerPtr& player : m_players)
		if (player->getID() == playerId)
			return player;
	return nullptr;
}

void Game::start()
{

}

void Game::processPlayerMove(uint32_t playerId, const Position2D& movePos)
{
	PlayerPtr player = getPlayer(playerId);
	if (!player)
		return;

	OutputMessage out;
}

void Game::processPlayerConnect(uint32_t playerId, const ProtocolGamePtr& c)
{
	if (m_players.size() == MAX_GAME_PLAYERS) {
		c->disconnect(NET_GAME_FULL);
		return;
	}

	PlayerPtr newPlayer(new Player);
	newPlayer->setID(playerId);
	newPlayer->setClient(c);
	m_players.push_back(newPlayer);

	PingHandler ph;
	ph.player = newPlayer;

	ph.start();
}

void Game::processPlayerDisconnect(uint32_t playerId)
{
	auto it = std::find_if(m_players.begin(), m_players.end(),
			[=] (const PlayerPtr& player) -> bool { return player->getID() == playerId; });
	if (it == m_players.end()) {
		g_logger.error(stdext::format("processPlayerDisconnect: cannot find player %d", playerId));
		return;
	}
	m_players.erase(it);

	auto iter  = std::find_if(m_pingHandlers.begin(), m_pingHandlers.end(),
			[=] (const PingHandler& ph) -> bool { return ph.player == (*it); });
	if (iter != m_pingHandlers.end()) {
		(*iter).stop();
		m_pingHandlers.erase(iter);
	}
}

void Game::processGameStart(uint32_t playerId)
{
	PlayerPtr player = getPlayer(playerId);
	if (!player)
		return;

	ProtocolGamePtr c = player->getClient();
	if (!c)
		return;

	if (player != *m_players.begin()) { 	// Game starter always the first player on the list
		player->sendErrorMessage("You're not the Game starter");
		return;
	}

	if (m_players.size() < MIN_GAME_PLAYERS) {
		player->sendErrorMessage(stdext::format("Not enough players to start the game; players needed: %d", MIN_GAME_PLAYERS));
		return;
	}

	OutputMessage out;

	out.addByte(NET_GAME_START);
	out.addString(stdext::format("Game will start in %d seconds.", SECONDS_TO_START_GAME));
	c->send(out);

	m_startEvent = g_sched.scheduleEvent(std::bind(&Game::start, this), SECONDS_TO_START_GAME * 1000, false);
}

void Game::processGameCancelStart(uint32_t playerId)
{
	PlayerPtr player = getPlayer(playerId);
	if (!player)
		return;

	if (player != *m_players.begin()) { 	// Game starter always the first player on the list
		player->sendErrorMessage("You're not the game starter");
		return;
	}

	if (!m_startEvent) {
		player->sendErrorMessage("The game has not been started");
		return;
	}

	g_sched.stopEvent(m_startEvent);
	player->sendStatusMessage("Game has been cancelled.");
}

