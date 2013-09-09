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
#include "chatserver.h"

#include <boost/algorithm/string.hpp>

ChatServer::ChatServer() :
	Server(g_config.getString("chathost"), g_config.getString("chatport"))
{

}

ChatServer::~ChatServer()
{

}

ProtocolChatPtr ChatServer::findConnection(const std::string& nick) const
{
	auto it = std::find_if(m_connections.begin(), m_connections.end(),
				[=] (const ProtocolChatPtr& pc) { return pc->getNick() == nick; });
	return it != m_connections.end() ? *it : nullptr;
}

void ChatServer::parseAdmins(const std::string& array)
{
	boost::split(m_admins, array, boost::is_any_of(";,"));
}

void ChatServer::newConnection(const ConnectionPtr& c)
{
	ProtocolChatPtr pc(new ProtocolChat);

	pc->setConnection(c);
	pc->setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2));
	pc->setNickChangeCallback(std::bind(&ChatServer::onNickChange, this, std::placeholders::_1, std::placeholders::_2));
	pc->setLeaveCallback(std::bind(&ChatServer::onLeave, this, std::placeholders::_1));
	pc->setJoinCallback(std::bind(&ChatServer::onJoin, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	m_connections.push_back(pc);
}

void ChatServer::onMessage(const std::string& from, const std::string& message)
{
	OutputMessage out;

	out.addByte(NET_CHAT_MESSAGE);
	out.addString(message);

	for (const ProtocolChatPtr& pc : m_connections)
		if (pc->getNick() != from)
			pc->send(out);
}

void ChatServer::onLeave(const std::string& who)
{
	auto it = std::find_if(m_connections.begin(), m_connections.end(),
				[=] (const ProtocolChatPtr& pc) { return pc->getNick() == who; });
	if (it == m_connections.end()) {
		g_logger.error(stdext::format("ChatServer::onLeave(): failed to find %s", who));
		return;
	}

	// Notify other users
	OutputMessage out;

	out.addByte(NET_CHAT_LEAVE);
	out.addString(who);
	for (const ProtocolChatPtr& pc : m_connections)
		pc->send(out);

	m_connections.erase(it);
}

void ChatServer::onNickChange(const std::string& oldNick, const std::string& newNick)
{
	const ProtocolChatPtr& pc = findConnection(oldNick);
	if (!pc) {
		g_logger.error(stdext::format("ChatServer::onNickChange(): Failed to find the user who changed his nick from %s to %s",
					oldNick, newNick));
		return;
	}

	// Notify other users
	OutputMessage out;

	out.addByte(NET_CHAT_NICKCHANGE);
	out.addString(oldNick);
	out.addString(newNick);

	for (const ProtocolChatPtr& __pc : m_connections)
		__pc->send(out);

	pc->__setNick(newNick);
}

void ChatServer::onJoin(const std::string& nick, const std::string& gameName, bool disconnectFromChat)
{
	const ProtocolChatPtr& pc = findConnection(nick);
	if (!pc) {
		g_logger.error(stdext::format("ChatServer::onJoin(): failed to find %s", nick));
		return;
	}

	// Notify other users
	OutputMessage out;

	out.addByte(NET_CHAT_JOINGAME);
	out.addString(nick);
	out.addString(gameName);
	out.addByte(disconnectFromChat);

	for (const ProtocolChatPtr& __pc : m_connections)
		if (__pc != pc)
			__pc->send(out);

	if (disconnectFromChat) {
		out.clear();

		out.addByte(NET_CHAT_LEAVE);
		out.addString(nick);

		pc->send(out);
	}
}

