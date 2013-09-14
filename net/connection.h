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
#ifndef __CONNECTION_H
#define __CONNECTION_H

#include "decl.h"
#include "outputmessage.h"

#include <list>

class Connection
	: public std::enable_shared_from_this<Connection>
{
	typedef std::function<void(uint8_t *, uint16_t)> ReadCallback;
public:
	Connection();
	~Connection();

	static void poll();

	void connect(const std::string& host, const std::string& port,
			const std::function<void()>& cb);
	void close();
	bool isConnected() const { return m_socket.is_open(); }

	inline void send(const OutputMessage& o) { write(o.data(), o.size()); }
	void write(const uint8_t *data, uint16_t bytes);
	void read(uint16_t bytes, const ReadCallback& rc);

	std::string getIP();

protected:
	void internalWrite(const boost::system::error_code& e);
	void handleConnect(const boost::system::error_code& e);
	void handleResolve(const boost::system::error_code& e,
				asio::ip::basic_resolver<asio::ip::tcp>::iterator endpointIterator);
	void handleWrite(const boost::system::error_code& e, size_t bytes,
			 std::shared_ptr<asio::streambuf> m_outputStream);
	void handleRead(const boost::system::error_code& e, size_t readSize);
	void handleError(const boost::system::error_code& e);

private:
	std::function<void()> m_connectCallback;
	ReadCallback m_readCallback;

	asio::deadline_timer m_delayedWriteTimer;
	asio::ip::tcp::socket m_socket;
	asio::ip::tcp::resolver m_resolver;

	static std::list<std::shared_ptr<asio::streambuf>> m_outputStreams;
	std::shared_ptr<asio::streambuf> m_outputStream;
	asio::streambuf m_inputStream;

	friend class Listener;
};

#endif

