#include "listener.h"

asio::io_service g_service;

Listener::Listener(const std::string& host, const std::string& port)
	: m_conn(new Connection())
{
	asio::ip::tcp::resolver res(g_service);
	asio::ip::tcp::resolver::query query(host, port);

	asio::ip::tcp::endpoint ep = *resolver.resolve(query);
	m_acceptor.open(ep.protocol());
	m_acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
	m_acceptor.bind(ep);
	m_acceptor.listen();
}

void Listener::poll(int numWorkers)
{
	std::vector<std::shared_ptr<std::thread>> threads;

	for (int i = 0; i < numWorkers; ++i) {
		std::shared_ptr<std::thread> thread(new std::thread(std::bind(&asio::io_service::run, &g_service)));
		threads.push_back(thread);
	}

	for (const auto& thread : threads)
		thread.join();
}

void Listener::start(const AcceptCallback& ac)
{
	m_acceptCallback = ac;
	m_acceptor.async_accept(m_conn->m_socket,
				std::bind(&Listener::handleConnection, shared_from_this(), asio::placeholders::error));
}

void Listener::handleConnection(const boost::system::error_code& error)
{
	if (error) {
		std::cerr << "Error accepting connection: " << error.message() << std::endl;
		return;
	}

	m_acceptCallback(m_conn);
	m_conn.reset(new Connection());
	m_acceptor.async_accept(m_client->m_socket,
				std::bind(&Listener::handleConnection, shared_from_this(),
					asio::placeholders::error));
}

