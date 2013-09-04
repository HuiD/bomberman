#include <net/listener.h>
#include <net/outputmessage.h>

int main(int argc, char *argv[])
{
	ListenerPtr li(new Listener("127.0.0.1", "6000"));

	li->start([=] (const ConnectionPtr& c) {
			OutputMessage out;

			out.addByte(0xFF);
			out.addString("Hello there");

			c->write(out.data(), out.size());
			});

	while (true)
		li->poll();

	return 0;
}

