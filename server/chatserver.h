#ifndef __CHATSERVER_H
#define __CHATSERVER_H

#include "server.h"
#include "../net/protocolchat.h"

class ChatServer : public Server
{
public:
	ChatServer();
	~ChatServer();

protected:
	void newConnection(const ConnectionPtr& c);

private:
	std::list<ProtocolChat> m_connections;
};

#endif

