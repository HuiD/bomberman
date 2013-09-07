#include "protocolchat.h"
#include "protocolbytes.h"

ProtocolChat::ProtocolChat()
{

}

ProtocolChat::~ProtocolChat()
{

}

void ProtocolChat::setNick(const std::string& nick)
{
	if (m_nick == nick)
		return;

	OutputMessage out;

	out.addByte(NET_CHAT_NICKCHANGE);
	out.addString(nick); 		// New Nickname
	out.addString(m_nick); 		// Old Nickname

	send(out);
	if (m_nickChangeCallback)
		m_nickChangeCallback(m_nick, nick);
	m_nick = nick;
}

void ProtocolChat::__setNick(const std::string& nick)
{
	if (m_nick == nick)
		return;

	if (m_nickChangeCallback)
		m_nickChangeCallback(m_nick, nick);
	m_nick = nick;
}

void ProtocolChat::recv()
{
	readBytes(DATA_SIZE, std::bind(&ProtocolChat::onRead, this, std::placeholders::_1, std::placeholders::_2));
}

void ProtocolChat::onConnect()
{
	OutputMessage out;

	out.addByte(NET_CHAT_WELCOME);
	out.addString("Welcome to the Chat Server");

	send(out);
	recv();
}

void ProtocolChat::onRead(uint8_t byte, InputMessage in)
{
	switch (byte) {
		case NET_CHAT_MESSAGE: {
			std::string from = in.getString();
			std::string message = in.getString();

			if (m_messageCallback)
				m_messageCallback(from, message);
			break;
		}
		case NET_CHAT_NICKCHANGE: {
			std::string newNick = in.getString();
			std::string oldNick = in.getString();

			if (m_nickChangeCallback)
				m_nickChangeCallback(oldNick, newNick);
			break;
		}
		case NET_CHAT_LEAVE: {
			std::string who = in.getString();

			if (m_leaveCallback)
				m_leaveCallback(who);
			break;
		} case NET_CHAT_JOINGAME: {
			std::string gameName = in.getString();
			if (m_joinCallback)
				m_joinCallback(getNick(), gameName);
			break;
		} default:
			g_logger.debug(stdext::format("Byte 0x%x not handled in the chat protocol", byte));
			break;
	}

	Protocol::onRead(byte, in);
	recv();
}

