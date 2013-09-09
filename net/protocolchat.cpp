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
			std::string nick = in.getString();
			std::string gameName = in.getString();
			bool disconnectFromChat = in.getByte() != (char)0;

			if (m_joinCallback)
				m_joinCallback(nick, gameName, disconnectFromChat);
			break;
		} default:
			g_logger.debug(stdext::format("Byte 0x%x not handled in the chat protocol", byte));
			break;
	}

	Protocol::onRead(byte, in);
	recv();
}

