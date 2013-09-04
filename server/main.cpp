#include <net/listener.h>

int main(int argc, char *argv[])
{
	ListenerPtr li(new Listener("127.0.0.1", "6000"));

	li->start([=] (const ConnectionPtr& c) { });

	while (true)
		li->poll();

	return 0;
}

