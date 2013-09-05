#ifndef __PROTOCOLCHAT_H
#define __PROTOCOLCHAT_H

#include "protocol.h"

class ProtocolChat : public Protocol
{
public:
	ProtocolChat();
	~ProtocolChat();

	void connect(const std::string& host, const std::string& port);
	void disconnect();

	void send(const std::string& message);
	void recv();

protected:
	void onConnect();
	void onRead(const InputMessage& in);

private:
	ConnectionPtr m_conn;
};

#endif

