#include "protocolchat.h"
#include "protocolbytes.h"

ProtocolChat::ProtocolChat()
{

}

ProtocolChat::~ProtocolChat()
{

}

void ProtocolChat::connect(const std::string& host, const std::string& port)
{
	m_conn = ConnectionPtr(new Connection);
	m_conn->connect(host, port, std::bind(&ProtocolChat::onConnect, this));
}

void ProtocolChat::disconnect()
{
	if (m_conn)
		m_conn->close();
	m_conn.reset();
}

void ProtocolChat::send(const std::string& message)
{
	if (!m_conn)
		return;

	OutputMessage msg;
	msg.addByte(NET_CHAT_MESSAGE);
	msg.addString(message);

	m_conn->write(msg.data(), msg.size());
}

void ProtocolChat::recv()
{
	if (m_conn)
		m_conn->read(DATA_SIZE, [=] (uint8_t *data, uint16_t size) {
					InputMessage in;
					in.setData(data);
					in.setSize(size);

					onRead(in);
				});
}

void ProtocolChat::onConnect()
{
	OutputMessage out;

	out.addByte(NET_CHAT_WELCOME);
	out.addString("Welcome to the Chat Server");

	m_conn->write(out.data(), out.size());
	recv();
}

void ProtocolChat::onRead(const InputMessage& in)
{

}

