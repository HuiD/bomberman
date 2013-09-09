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
#include "protocolgame.h"
#include "protocolbytes.h"

ProtocolGame::ProtocolGame()
{

}

ProtocolGame::~ProtocolGame()
{

}

void ProtocolGame::disconnect(uint8_t reason)
{
	getConnection()->write(&reason, 1);
	getConnection()->close();
}

void ProtocolGame::recv()
{
	readBytes(DATA_SIZE, std::bind(&ProtocolGame::onRead, this, std::placeholders::_1, std::placeholders::_2));
}

void ProtocolGame::sendPing()
{
	uint8_t tmp = NET_PING;
	getConnection()->write(&tmp, 1);
}

void ProtocolGame::onConnect()
{
	OutputMessage out;

	out.addByte(NET_GAME_WELCOME);
	out.addString("Welcome to the game server");

	send(out);
	recv();
}

void ProtocolGame::onRead(uint8_t byte, InputMessage in)
{
	if (byte < NET_GAME_START || byte > NET_GAME_PLAYER_DEAD)
		Protocol::onRead(byte, in);
	else if (m_byteHandler)
		m_byteHandler(in.getU32(), byte, in);

	recv();
}

