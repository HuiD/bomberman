#ifndef __PROTOCOLGAME_H
#define __PROTOCOLGAME_H

#include "protocol.h"

class ProtocolGame : public Protocol
{
	typedef std::function<void(uint32_t playerId, uint8_t byteSent, InputMessage in)> ByteHandler;

public:
	ProtocolGame();
	~ProtocolGame();

	void disconnect(uint8_t reason);
	void setByteHandler(const ByteHandler& bh) { m_byteHandler = bh; }
	void recv();
	void sendPing();

protected:
	void onConnect();
	void onRead(uint8_t byte, InputMessage in);

private:
	ByteHandler m_byteHandler;
};

#endif

