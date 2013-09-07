#include "listener.h"

#include <thread>
#include <vector>

asio::io_service g_service;

Listener::Listener(const std::string& host, const std::string& port) :
	m_closed(false),
	m_acceptor(g_service)
{
	asio::ip::tcp::endpoint ep;

	if (host.empty()) {
		asio::ip::tcp::endpoint _ep(asio::ip::tcp::v4(), atoi(port.c_str()));
		ep = _ep;
	} else {
		asio::ip::tcp::resolver res(g_service);
		asio::ip::tcp::resolver::query query(host, port);

		ep = *res.resolve(query);
	}

	m_acceptor.open(ep.protocol());
	m_acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
	m_acceptor.bind(ep);
	m_acceptor.listen();
}

Listener::~Listener()
{

}

void Listener::poll()
{
	g_service.poll();
	g_service.reset();
}

void Listener::start(const AcceptCallback& ac)
{
	if (m_closed)
		return;

	ConnectionPtr conn(new Connection());
	m_acceptor.async_accept(conn->m_socket,
				[=] (const boost::system::error_code& error) {
					if (error) {
						g_logger.error(stdext::format("Error accepting connection: %s", error.message()));
						return;
					}

					ac(conn);
					start(ac);
				});
}

