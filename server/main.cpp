#include "../net/connection.h"
#include "../net/listener.h"
#include "../net/protocolchat.h"

int main(int argc, char *argv[])
{
	ListenerPtr listener(new Listener("127.0.0.1", "6000"));

	listener->start(
		[=] (const ConnectionPtr& c) {
			ProtocolChat pc;

			pc.setConnection(c);
	});
	listener->poll();

	return 0;
}

