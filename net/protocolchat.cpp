#include "protocolchat.h"
#include "protocolbytes.h"

ProtocolChat::ProtocolChat()
{

}

ProtocolChat::~ProtocolChat()
{

}

void ProtocolChat::setNick(const std::string& nick)
{
	if (m_nick == nick)
		return;

	if (m_nickChangeCallback)
		m_nickChangeCallback(m_nick, nick);
	m_nick = nick;

	OutputMessage out;

	out.addByte(NET_CHAT_NICKCHANGE);
	out.addString(nick);

	send(out);
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

void ProtocolChat::recv()
{
	if (m_conn)
		m_conn->read(DATA_SIZE, [=] (uint8_t *data, uint16_t size) {
					InputMessage in;
					in.setData(data);
					in.setSize(size);

					onRead(in.getByte(), in);
				});
}

void ProtocolChat::onConnect()
{
	OutputMessage out;

	out.addByte(NET_CHAT_WELCOME);
	out.addString("Welcome to the Chat Server");

	send(out);
	recv();
}

void ProtocolChat::onRead(uint8_t byte, InputMessage in)
{
	switch (byte) {
		case NET_CHAT_MESSAGE: {
			std::string message = in.getString();
			if (m_messageCallback)
				m_messageCallback(m_nick, message);
			break;
		}
		case NET_CHAT_NICKCHANGE:
			setNick(in.getString());
			break;
		case NET_CHAT_LEAVE:
			if (m_leaveCallback)
				m_leaveCallback();
			disconnect();
			break;
		default:
			g_logger.warning("invalid byte sent for chat");
			break;
	}

	Protocol::onRead(byte, in);
}

