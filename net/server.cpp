#include "server.h"

Server::Server(const std::string& host, const std::string& port)
{
	m_listener = ListenerPtr(new Listener(host, port));
}

Server::~Server()
{
	m_listener = nullptr;
}

void Server::start()
{
	m_listener->start(std::bind(&Server::newConnection, this, std::placeholders::_1));
}

void Server::closeTemporarily()
{
	m_listener->close();
}

