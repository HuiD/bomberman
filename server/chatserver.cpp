#include "chatserver.h"

#include <boost/algorithm/string.hpp>

ChatServer::ChatServer() :
	Server(g_config.getString("chathost"), g_config.getString("chatport"))
{

}

ChatServer::~ChatServer()
{

}

void ChatServer::parseAdmins(const std::string& array)
{
	boost::split(m_admins, array, boost::is_any_of(";,"));
}

void ChatServer::newConnection(const ConnectionPtr& c)
{
	printf("New connection\n");
	ProtocolChatPtr pc(new ProtocolChat);

	pc->setConnection(c);
	m_connections.push_back(pc);
}

