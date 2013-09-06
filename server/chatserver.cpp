#include "chatserver.h"

ChatServer::ChatServer() :
	Server(g_config.getString("chathost"), g_config.getString("chatport"))
{

}

ChatServer::~ChatServer()
{

}

void ChatServer::newConnection(const ConnectionPtr& c)
{
	ProtocolChat pc;

	pc.setConnection(c);
	m_connections.push_back(pc);
}

