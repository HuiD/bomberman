#include "server.h"

Server::Server(const std::string& host, const std::string& port)
{
	m_listener = ListenerPtr(new Listener(host, port));
	m_listener->start(std::bind(&Server::newConnection, this, std::placeholders::_1));
}

Server::~Server()
{

}

