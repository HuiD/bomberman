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
	m_conn = ConnectionPtr(new Connection());
	m_conn->connect(host, port, std::bind(&Protocol::onConnect, this));
}

void Protocol::disconnect()
{
	if (m_conn)
		m_conn->close();
	m_conn.reset();
}

void Protocol::send(const OutputMessage& out)
{
	if (!m_conn)
		return;

	m_conn->write(out.data(), out.size());
}

void Protocol::onConnect()
{
	recv();
}

void Protocol::onRead(uint8_t byte, InputMessage in)
{
	switch (byte) {
		case NET_PONG:
			break;
		default:
			break;
	}
}

