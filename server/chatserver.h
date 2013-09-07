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

private:
	std::list<std::string> m_admins;
	std::list<ProtocolChatPtr> m_connections;
};

#endif

