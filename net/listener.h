#ifndef __LISTENER_H
#define __LISTENER_H

#include "decl.h"

class Listener :
	public std::enable_shared_from_this<Listener>
{
	typedef std::function<void(const ConnectionPtr& )> AcceptCallback;

public:
	Listener();
	~Listener();

	static void poll(int numWorkers);
	void start(const AcceptCallback& ac);

protected:
	void handleConnection(const boost::system::error_code& e);

	AcceptCallback m_acceptCallback;
	ConnectionPtr m_connection;
	asio::ip::tcp::acceptor m_acceptor;
};

#endif

