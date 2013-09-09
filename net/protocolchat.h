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
#ifndef __PROTOCOLCHAT_H
#define __PROTOCOLCHAT_H

#include "protocol.h"

class ProtocolChat : public Protocol
{
	typedef std::function<void(const std::string& nick, const std::string& message)> MessageCallback;
	typedef std::function<void(const std::string& nick)> LeaveCallback;
	typedef std::function<void(const std::string& oldNick, const std::string& newNick)> NickChangeCallback;
	typedef std::function<void(const std::string& who, const std::string& gameName, bool disconnectFromChat)> JoinCallback;

public:
	ProtocolChat();
	~ProtocolChat();

	std::string getNick() const { return m_nick; }
	void setNick(const std::string& nick);
	void __setNick(const std::string& nick);

	void recv();

	void setMessageCallback(const MessageCallback& cb) { m_messageCallback = cb; }
	void setLeaveCallback(const LeaveCallback& cb) { m_leaveCallback = cb; }
	void setNickChangeCallback(const NickChangeCallback& cb) { m_nickChangeCallback = cb; }
	void setJoinCallback(const JoinCallback& jc) { m_joinCallback = jc; }

protected:
	void onConnect();
	void onRead(uint8_t byte, InputMessage in);

private:
	std::string m_nick;

	MessageCallback m_messageCallback;
	LeaveCallback m_leaveCallback;
	NickChangeCallback m_nickChangeCallback;
	JoinCallback m_joinCallback;
};

#endif

