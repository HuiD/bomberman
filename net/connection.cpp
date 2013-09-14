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
#include "connection.h"

extern asio::io_service g_service;
std::list<std::shared_ptr<asio::streambuf>> Connection::m_outputStreams;

Connection::Connection() :
	m_delayedWriteTimer(g_service),
	m_socket(g_service),
	m_resolver(g_service)
{

}

Connection::~Connection()
{
	close();
}

void Connection::poll()
{
	g_service.poll();
	g_service.reset();
}

void Connection::connect(const std::string& host, const std::string& port,
		const std::function<void()>& cb)
{
	m_connectCallback = cb;

	asio::ip::tcp::resolver::query query(host, port);
	m_resolver.async_resolve(query,
				std::bind(&Connection::handleResolve, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void Connection::close()
{
	if (!m_socket.is_open()) {
		g_logger.error(stdext::format("Connection::close(): Called on an already closed connection!"));
		return;
	}

	boost::system::error_code ec;

	m_socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
	if (ec)
		g_logger.error(stdext::format("Failed to shutdown socket: %s", ec.message()));
	m_socket.close();
}

void Connection::write(const uint8_t *bytes, uint16_t size)
{
	if (!isConnected())
		return;

	if (!m_outputStream) {
		if (!m_outputStreams.empty()) {
			m_outputStream = m_outputStreams.front();
			m_outputStreams.pop_front();
		} else
			m_outputStream = std::shared_ptr<asio::streambuf>(new asio::streambuf);

		m_delayedWriteTimer.cancel();
		m_delayedWriteTimer.expires_from_now(boost::posix_time::milliseconds(10));
		m_delayedWriteTimer.async_wait(std::bind(&Connection::internalWrite, shared_from_this(), std::placeholders::_1));
	}

	std::ostream os(m_outputStream.get());
	os.write((const char *)bytes, size);
	os.flush();
}

void Connection::read(uint16_t bytes, const ReadCallback& rc)
{
	if (!isConnected())
		return;

	m_readCallback = rc;
	m_socket.async_read_some(asio::buffer(m_inputStream.prepare(bytes)),
			 std::bind(&Connection::handleRead, shared_from_this(),
				 std::placeholders::_1, std::placeholders::_2));
}

void Connection::internalWrite(const boost::system::error_code& e)
{
	if (e == asio::error::operation_aborted)
		return;

	std::shared_ptr<asio::streambuf> outputStream = m_outputStream;
	m_outputStream = nullptr;

	asio::async_write(m_socket,
			   *outputStream,
			   std::bind(&Connection::handleWrite, shared_from_this(),
				   std::placeholders::_1, std::placeholders::_2, outputStream));
}

void Connection::handleResolve(const boost::system::error_code& e, asio::ip::basic_resolver<asio::ip::tcp>::iterator endpointIter)
{
	if (e == asio::error::operation_aborted)
		return;

	if (!e)
		m_socket.async_connect(*endpointIter, std::bind(&Connection::handleConnect, shared_from_this(), std::placeholders::_1));
	else
		handleError(e);
}

void Connection::handleConnect(const boost::system::error_code& e)
{
	if (e == asio::error::operation_aborted)
		return;

	if (!e) {
		m_socket.set_option(asio::ip::tcp::no_delay(true));
		if (m_connectCallback)
			m_connectCallback();
	} else
		handleError(e);
}

void Connection::handleError(const boost::system::error_code& error)
{
	if (error == asio::error::operation_aborted)
		return;

	g_logger.error(stdext::format("Connection error: %s", error.message()));
	close();
}

void Connection::handleWrite(const boost::system::error_code& e, size_t size,
				std::shared_ptr<asio::streambuf> outputStream)
{
	m_delayedWriteTimer.cancel();
	if (e == asio::error::operation_aborted)
		return;

	outputStream->consume(outputStream->size());
	m_outputStreams.push_back(outputStream);
	if (e)
		handleError(e);
}

void Connection::handleRead(const boost::system::error_code& e, size_t readSize)
{
	if (e == asio::error::operation_aborted)
		return;

	if (!e) {
		if (m_readCallback) {
			const char *data = asio::buffer_cast<const char *>(m_inputStream.data());
			m_readCallback((uint8_t *)data, readSize);
		}

		m_inputStream.consume(readSize);
	} else
		handleError(e);
}

