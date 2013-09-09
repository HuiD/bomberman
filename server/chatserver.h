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
#ifndef __CHATSERVER_H
#define __CHATSERVER_H

#include "../net/server.h"
#include "../net/protocolchat.h"

class ChatServer : public Server
{
public:
	ChatServer();
	~ChatServer();

	void parseAdmins(const std::string& array);

protected:
	void newConnection(const ConnectionPtr& c);
	void onNickChange(const std::string& oldNick, const std::string& newNick);
	void onLeave(const std::string& who);
	void onMessage(const std::string& from, const std::string& message);
	void onJoin(const std::string& who, const std::string& gameName, bool dc);

	ProtocolChatPtr findConnection(const std::string& nick) const;

private:
	std::list<std::string> m_admins;
	std::list<ProtocolChatPtr> m_connections;
};

#endif

