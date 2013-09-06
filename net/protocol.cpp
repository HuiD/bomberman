#include "protocol.h"
#include "protocolbytes.h"

Protocol::Protocol() :
	m_conn(nullptr)
{

}

Protocol::~Protocol()
{

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

