/*
 * Copyright (c) 2013 Ahmed Samy  <f.fallen45@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
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

