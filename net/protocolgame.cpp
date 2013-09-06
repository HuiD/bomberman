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

