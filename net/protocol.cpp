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
#include "protocol.h"
#include "protocolbytes.h"

Protocol::Protocol() :
	m_conn(nullptr)
{

}

Protocol::~Protocol()
{

}

void Protocol::connect(const std::string& host, const std::string& port)
{
	if (!m_conn)
		m_conn = ConnectionPtr(new Connection());

	if (m_conn->isConnected()) {
		g_logger.info(stdext::format("Protocol::connect(): Already connected, reconnecting..."));
		m_conn->close();
	}

	m_conn->connect(host, port, std::bind(&Protocol::onConnect, this));
}

void Protocol::disconnect()
{
	if (m_conn && m_conn->isConnected())
		m_conn->close();
	m_conn.reset();
}

void Protocol::send(const OutputMessage& out)
{
	if (!m_conn)
		return;

	m_conn->write(out.data(), out.size());
}

void Protocol::readBytes(size_t size, const std::function<void(uint8_t, InputMessage)>& cb)
{
	m_conn->read(size,
		[=] (uint8_t *data, uint16_t size) {
			InputMessage in;
			in.setData(data);
			in.setSize(size);

			cb(in.getByte(), in);
	});
}

void Protocol::onRead(uint8_t byte, InputMessage in)
{
	uint8_t tmp = NET_PONG;
	if (byte == NET_PING)
		m_conn->write(&tmp, 1);
}

