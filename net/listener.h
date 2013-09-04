#ifndef __LISTENER_H
#define __LISTENER_H

#include "decl.h"

#include "connection.h"

class Listener
{
	typedef std::function<void(const ConnectionPtr& )> AcceptCallback;

public:
	Listener(const std::string& host, const std::string& port);
	~Listener();

	static void poll();
	void start(const AcceptCallback& ac);

protected:
	asio::ip::tcp::acceptor m_acceptor;
};

#endif

