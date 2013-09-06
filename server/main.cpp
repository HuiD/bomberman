#include "../net/connection.h"
#include "../net/listener.h"
#include "../net/protocolchat.h"
#include "../util/configmanager.h"

int main(int argc, char *argv[])
{
	// Load configuration
	if (!g_config.loadFrom("server.cfg")) {
		g_logger.error(stdext::format("failed to load configuration from 'server.cfg'"));
		return 1;
	}

	ListenerPtr listener(new Listener("127.0.0.1", "6000"));

	listener->start(
		[=] (const ConnectionPtr& c) {
			ProtocolChat pc;

			pc.setConnection(c);
		}
	);
	listener->poll();

	return 0;
}

