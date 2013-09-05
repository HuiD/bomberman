#include "protocol.h"

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

void Protocol::recv()
{
	if (m_conn)
		m_conn->read(DATA_SIZE, [=](uint8_t *data, uint16_t size) {
						InputMessage in;

						in.setSize(size);
						in.setData(data);
						onRead(in);
					});
}

void Protocol::onConnect()
{
	recv();
}

void Protocol::onRead(const InputMessage& in)
{

}

