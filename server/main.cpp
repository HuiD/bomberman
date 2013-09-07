#include "../util/configmanager.h"
#include "chatserver.h"

int main(int argc, char *argv[])
{
	// Load configuration
	if (!g_config.loadFrom("server.cfg")) {
		g_logger.error(stdext::format("failed to load configuration from 'server.cfg'"));
		return 1;
	}

	ChatServer cs;

	cs.start();
	while (true)
		cs.poll();

	return 0;
}

