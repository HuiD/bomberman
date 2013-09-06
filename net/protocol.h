#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "decl.h"

#include "inputmessage.h"
#include "outputmessage.h"

#include "connection.h"

class Protocol
{
public:
	Protocol();
	virtual ~Protocol();

	void connect(const std::string& host, const std::string& port);
	void disconnect();

	ConnectionPtr getConnection() const { return m_conn; }
	void setConnection(const ConnectionPtr& c)
	{
		m_conn = c;
		if (c)
			onConnect();
	}

	virtual void send(const OutputMessage& out);
	virtual void recv() =0;

	void readBytes(size_t size, const std::function<void(uint8_t, InputMessage)>& cb);

protected:
	virtual void onConnect() = 0;
	virtual void onRead(uint8_t byte, InputMessage in);

private:
	ConnectionPtr m_conn;
};

#endif

