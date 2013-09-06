#ifndef __BASE_SERVER_H
#define __BASE_SERVER_H

#include "decl.h"
#include "../net/connection.h"
#include "../net/listener.h"

class Server
{
public:
	Server(const std::string& host, const std::string& port);
	virtual ~Server();

	ListenerPtr getListener() const { return m_listener; }
	inline void poll() { m_listener->poll(); }

protected:
	virtual void newConnection(const ConnectionPtr& c) = 0;

private:
	ListenerPtr m_listener;
};

#endif

