#ifndef __PROTOCOLCHAT_H
#define __PROTOCOLCHAT_H

#include "protocol.h"

class ProtocolChat : public Protocol
{
	typedef std::function<void(const std::string& nick, const std::string& message)> MessageCallback;
	typedef std::function<void(const std::string& nick)> LeaveCallback;
	typedef std::function<void(const std::string& oldNick, const std::string& newNick)> NickChangeCallback;

public:
	ProtocolChat();
	~ProtocolChat();

	std::string getNick() const { return m_nick; }
	void setNick(const std::string& userName);

	void recv();

	void setMessageCallback(const MessageCallback& cb) { m_messageCallback = cb; }
	void setLeaveCallback(const LeaveCallback& cb) { m_leaveCallback = cb; }
	void setNickChangeCallback(const NickChangeCallback& cb) { m_nickChangeCallback = cb; }

protected:
	void onConnect();
	void onRead(uint8_t byte, InputMessage in);

private:
	std::string m_nick;

	MessageCallback m_messageCallback;
	LeaveCallback m_leaveCallback;
	NickChangeCallback m_nickChangeCallback;
};

#endif

