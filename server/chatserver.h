#ifndef __CHATSERVER_H
#define __CHATSERVER_H

#include "../net/server.h"
#include "../net/protocolchat.h"

class ChatServer : public Server
{
public:
	ChatServer();
	~ChatServer();

	void parseAdmins(const std::string& array);

protected:
	void newConnection(const ConnectionPtr& c);
	void onNickChange(const std::string& oldNick, const std::string& newNick);
	void onLeave(const std::string& who);
	void onMessage(const std::string& from, const std::string& message);
	void onJoin(const std::string& who, const std::string& gameName, bool dc);

	ProtocolChatPtr findConnection(const std::string& nick) const;

private:
	std::list<std::string> m_admins;
	std::list<ProtocolChatPtr> m_connections;
};

#endif

