#include "gui/mainwindow.h"

std::string g_progname;

int main(int argc, char *argv[])
{
	g_progname = argv[0];

	g_window.init();
	g_window.show();

	while (!g_window.isClosed())
		g_window.poll();

	return 0;
}

