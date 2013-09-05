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
	void setConnection(const ConnectionPtr& c) { m_conn = c; }

	virtual void send(const OutputMessage& out);
	virtual void recv();

protected:
	virtual void onConnect();
	virtual void onRead(const InputMessage& in);

private:
	ConnectionPtr m_conn;
};

#endif

