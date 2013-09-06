#include "listener.h"

#include <thread>
#include <vector>

asio::io_service g_service;

Listener::Listener(const std::string& host, const std::string& port) :
	m_acceptor(g_service)
{
	asio::ip::tcp::resolver res(g_service);
	asio::ip::tcp::resolver::query query(host, port);

	asio::ip::tcp::endpoint ep = *res.resolve(query);
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

