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

